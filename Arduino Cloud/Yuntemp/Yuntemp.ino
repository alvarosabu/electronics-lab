
#include <Bridge.h>
#include <BridgeSSLClient.h>
#include <ArduinoCloud.h>

#define analogPin  A0 //the thermistor attach to 
#define beta 4090 //the beta of the thermistor
#define resistance 10 //the value of the pull-down resistor

// Arduino Cloud settings and credentials
const char userName[]   = "alvarosaburido";
const char thingName[] = "yuntemp";
const char thingId[]   = "96a0f1ec-3962-4ac1-bd5d-8c5e69a98f77";
const char thingPsw[]  = "d595d862-ddc9-4c85-aa80-2300a6fd0036";

long adc = 0;

BridgeSSLClient sslClient;


// build a new object "yuntemp"
ArduinoCloudThing yuntemp;


void setup() {
  Serial.begin (9600);

  Serial.println("Starting Bridge");
  Bridge.begin();
  Serial.println("Done");


  yuntemp.begin(thingName, userName, thingId, thingPsw, sslClient);
  yuntemp.enableDebug();
  // define the properties
  yuntemp.addProperty("temp", CHARSTRING, R, TIMED, 1);
  
}

void loop() {
  adc = analogRead(analogPin);
  adc = 1023 - adc;
   //the calculating formula of temperature
  float tempC = beta /(log((1025.0 * 10 / adc - 10) / 10) + beta / 298.0) - 273.0;
  float tempF = tempC + 273.15;
  yuntemp.poll();
  Serial.print(tempC);
  Serial.println(" ªC");
  yuntemp.writeProperty("temp", "oh...");
  
  delay(1000);
  yuntemp.writeProperty("temp", "yeah!");
  
  delay(1000);
}

