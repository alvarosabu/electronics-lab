#include "Waveforms.h"

#define oneHzSample 1000000/maxSamplesNum

volatile int wave0 = 0;
int i = 0;

void setup() {
    Serial.begin(9600);
}

// Next is the loop function...

void loop() {
  analogWrite(DAC, waveformsTable[wave0][i]);  // write the selected waveform on DAC0
  Serial.println(waveformsTable[wave0][i]);

  i++;
  if(i == maxSamplesNum)  // Reset the counter to repeat the wave
    i = 0;

  delayMicroseconds(1000000);  // Hold the sample value for the sample time

}
