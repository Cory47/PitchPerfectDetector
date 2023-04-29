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
const float baseFrequency = 16.35; // Frequency of C0 String 

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

  

   pinMode(LED_BUILTIN, OUTPUT);
}



void loop() {
  int x = analogRead(A0);
  Serial.println(x);
  if(x < 1){
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
    if(!isnan(peak) && note != curNote) {
      Serial.println(curNote);
      note = curNote;
    }
  }
  
}
