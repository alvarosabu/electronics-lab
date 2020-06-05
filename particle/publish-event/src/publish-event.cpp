/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/alvarosaburido/as/electronics/electronics-lab/Particle/publish-event/src/publish-event.ino"
/*
 * Project publish-event
 * Description:
 * Author:
 * Date:
 */

void readBatteryLevel();
void setup();
void loop();
#line 8 "/Users/alvarosaburido/as/electronics/electronics-lab/Particle/publish-event/src/publish-event.ino"
#define LOW_BATTERY_THREESHOLD 1
#define VCC 5.0
#define LEVELS 4095

int battery = A0;

void readBatteryLevel() {
  int adc = analogRead(battery);
  float batteryLevel = (adc * VCC) / LEVELS;
  Serial.println(batteryLevel);
  if (batteryLevel <= LOW_BATTERY_THREESHOLD) {
    bool success = Particle.publish("low-battery", batteryLevel + "V", PRIVATE);
    if (!success) {
      // get here if event publish did not work
      Serial.println("Couldn't publish event");
    }
    Serial.println("Event published succesffully");
  }
  delay(1000);
}

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Serial.begin(9600);
  pinMode(battery,INPUT);  // Our photoresistor pin is input (reading the photoresistor)
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
  readBatteryLevel();
  delay(500);
}
