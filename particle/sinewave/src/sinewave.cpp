/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/alvarosaburido/as/electronics/electronics-lab/Particle/sinewave/src/sinewave.ino"
#include <SineWave.h>
#include <TimerOne.h>

void setup();
void loop();
#line 4 "/Users/alvarosaburido/as/electronics/electronics-lab/Particle/sinewave/src/sinewave.ino"
void setup()
{
  sw.setInterval(50);
  sw.setPin(5);

}

void loop()
{
  for(int i=0; i<10; i++){
    sw.playTone(500+i*10, 500);
  }
  for(int i=0; i<10; i++){
    sw.playTone2(500, 500+i*10, 500);
  }
  sw.stopTone();
  sw.setInterval(60);
  sw.playTone2(500, 600);
  delay(1000);
  sw.stopTone();
}
