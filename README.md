**Pitch Perfect**
______________________________
Task: Created as an extra credit project for CS 334: Operating systems, the task is to create a system using an Arduino Uno that can detect the pitch of audio input from a microphone and display the corresponding note on the serial monitor. Conceptually, this is a pitch detector, for determining if an instrument is out of tune, and can be used to tune it back to the correct note.

**Design:**

The design consists of the following components:

Arduino Uno
Microphone module with an analog output
Breadboard
Jumper wires
Resistors

Design Photos:

![Screenshot 2024-02-13 at 10 04 12 PM](https://github.com/Cory47/PitchPerfectDetector/assets/83315406/3621fa0d-e2b4-4132-88a6-d33d0b6cd4a6)

Design Flow: High Level overview of the project plan. Shows the flow of audio from speaker to display of note.
![Screenshot 2024-02-13 at 10 04 23 PM](https://github.com/Cory47/PitchPerfectDetector/assets/83315406/f486bf28-6f6e-431a-99bd-692e7c6f9083)

Breadboard Design: Shows how there is one light for each note, and another light for if the note is sharp. 
Implementation:

The code for the Arduino Uno is designed to detect the pitch of an audio input from a microphone and display the corresponding musical note on the serial monitor. Here's a high-level overview of the code and the transformations it performs:

Import necessary libraries: The code imports the arduinoFFT library for performing Fast Fourier Transform (FFT) calculations, the Arduino library for general functions, the math library for mathematical operations, and the log2 library for calculating logarithms in base 2.

Define constants: The code defines several constants for use throughout the program, including the number of samples for the FFT, the sampling frequency, the number of notes, and the base frequency for the note C0.

Initialize variables: The code initializes several variables, including arrays for storing real and imaginary values of the FFT, and a variable to store the detected note.

Define the getNoteFromFrequency() function: This function takes a frequency value as input and returns the corresponding musical note as a string. The function calculates the note index by taking the logarithm base 2 of the frequency divided by the base frequency, then scales it by 12 (the number of notes in an octave). The note index is then used to determine the octave and the note within the octave.

Set up the Arduino: The code sets up the Arduino with a specific baud rate for the serial monitor and calculates the sampling period based on the sampling frequency.

Main loop: The code continuously executes the following steps in the main loop:
a. Read the analog input from the microphone and store it in the vReal array.
b. Perform a windowing operation on the real values using a Hamming window to reduce spectral leakage during the FFT.
c. Compute the FFT using the windowed real values and imaginary values initialized to zero.
d. Convert the complex FFT output (real and imaginary values) to magnitudes.
e. Find the peak frequency in the magnitude spectrum using the MajorPeak() function.
f. Convert the peak frequency to the corresponding musical note using the getNoteFromFrequency() function.
g. Display the detected note on the serial monitor if it has changed since the last iteration.

Through these steps, the code takes the audio input from the microphone, processes it using the FFT to determine its frequency spectrum, identifies the peak frequency, and maps it to the corresponding musical note, which is then displayed on the serial monitor.

Use the provided code to detect the pitch of the audio input and display the corresponding note on the serial monitor.

Test Plan and Results:
The test plan includes the following test cases:

Test Case 1:

Input a specific note (e.g., A4 at 440 Hz) using a musical instrument or a tone generator app

Expected result: The detected note should be displayed as "A4" on the serial monitor.

Test Case 2: 

Input a series of different notes using a musical instrument or a tone generator app

Expected result: The detected notes should be displayed on the serial monitor in the order they were played.

To execute the test plan, follow these steps:

Upload the provided code to the Arduino Uno.
Open the Arduino IDE Serial Monitor, and set the baud rate to 115200.
Perform each test case and observe the serial monitor for the displayed notes.
For each test case, compare the expected results with the actual results shown on the serial monitor. If the expected and actual results match, the test case is successful.
