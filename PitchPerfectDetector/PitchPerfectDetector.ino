#include "arduinoFFT.h"
#include <Arduino.h>
#include <math.h>
#include "log2.h"

#define SAMPLES 128
#define SAMPLING_FREQUENCY 2048

arduinoFFT FFT = arduinoFFT();
unsigned int samplingPeriod;
unsigned long microSeconds;
double vReal[SAMPLES];
double vImag[SAMPLES];
String note;

const int numNotes = 12;
const char* notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
const float baseFrequency = 16.35;
const int sharpIndicatorPin = 2;
const int naturalNotePins[] = {3, 4, 5, 6, 7, 8, 9};

String getNoteFromFrequency(double frequency) {
  int noteIndex = round(12 * log2(frequency / baseFrequency));
  int octave = noteIndex / 12;
  int noteInOctave = noteIndex % 12;
  if (noteInOctave < 0) {
    noteInOctave += numNotes;
    octave -= 1;
  }
  return String(notes[noteInOctave]) + String(octave);
}

void setup() {
  Serial.begin(115200);
  samplingPeriod = round(1000000 * (1.0 / SAMPLING_FREQUENCY));

  pinMode(sharpIndicatorPin, OUTPUT);
  for (int i = 0; i < 7; i++) {
    pinMode(naturalNotePins[i], OUTPUT);
  }
}

void loop() {
  int x = analogRead(A0);
  Serial.println(x);
  if (x < 1) {
    for (int i = 0; i < SAMPLES; i++) {
      microSeconds = micros();
      vReal[i] = digitalRead(7);
      vImag[i] = 0;

      while (micros() < (microSeconds + samplingPeriod)) {
      }
    }

    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    String curNote = getNoteFromFrequency(peak);
    if (!isnan(peak) && note != curNote) {
      Serial.println(curNote);
      note = curNote;

      // Turn off all LEDs
      digitalWrite(sharpIndicatorPin, LOW);
      for (int i = 0; i < 7; i++) {
        digitalWrite(naturalNotePins[i], LOW);
      }

      // Turn on LED for the detected note
      int noteIndex = curNote.indexOf('#');
      if (noteIndex != -1) {
        digitalWrite(sharpIndicatorPin, HIGH);
        curNote.remove(noteIndex, 1);
      }
      int naturalNoteIndex = (curNote[0] - 'A' + 5) % 7; // Convert A, B, C, D, E, F, G to 5, 6, 0, 1, 2, 3, 4
      digitalWrite(naturalNotePins[naturalNoteIndex], HIGH);
    }
  }
}
