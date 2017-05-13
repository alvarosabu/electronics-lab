


/*
  YunSensorMote

   A Sensor Mote using Arduino Yun that comunicates vía Wifi 
   through REST calls using the Bridge Library.

   It use a JSONp library to return json objects with the raw data.
   
     The Circuit:
  * Arduino A0 connected to Vout signal pin of Analog Temperature Sensor.
  * Arduino A1 connected to Vout signal pin of Humidity DHT11 Sensor.
  * Arduino A2 connected to Vout signal pin of Linear Hall Effect Sensor.
  * Arduino A3 connected to a 10K Pot that will simulate any other analog sensor.
  * Arduino D8 connected to Relay Module

  The Date:
  created 06 May 2017

  The Author:
  by Alvaro Saburido Rodriguez
  alvaro.saburido@gmail.com

  This example code is in the public domain. Please share and enjoy
*/

#include <Bridge.h>
#include <BridgeServer.h>
#include <BridgeClient.h>
#include <dht.h>
#include <ArduinoJson.h>

#define MOTEID 1 // Mote ID

#define beta 4090 //the beta of the thermistor

int tempPin = A0; // Select the input from Analog Temperature Sensor
int humidityPin = A1; // Select the input from Humidity DHT11 Sensor
int hallPin = A2; // Select the input from Linear Hall Effect Sensor
int adcPin = A3; // Select the input from Custom Analog Sensor(POT).
int relayPin = 8; // Output to Relay Module.
int ledPin = 13;

int groupId = 2;
int temp = 0;
float humidity = 0;
int hall = 0;
int adc = 0;
int relay = 0;
BridgeServer server;
// Inside the brackets, 200 is the size of the pool in bytes.
// If the JSON object is more complex, you need to increase that value.
StaticJsonBuffer<100> jsonBuffer;
// It's a reference to the JsonObject, the actual bytes are inside the
// JsonBuffer with all the other nodes of the object tree.
// Memory is freed when jsonBuffer goes out of scope.
JsonObject& dataJson = jsonBuffer.createObject();
JsonObject& sensorJson = jsonBuffer.createObject();

// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
dht DHT;
void setup() {
  // put your setup code here, to run once:
  // Bridge startup
  pinMode(13, OUTPUT);
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600); 

  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);
  
  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();
}

void loop() {
  Serial.print("DHT11, \t");
  int chk = DHT.read11(humidityPin);
   switch (chk)
  {
    case DHTLIB_OK:  
    Serial.print("OK,\t"); 
    break;
    case DHTLIB_ERROR_CHECKSUM: 
    Serial.print("Checksum error,\t"); 
    break;
    case DHTLIB_ERROR_TIMEOUT: 
    Serial.print("Time out error,\t"); 
    break;
    default: 
    Serial.print("Unknown error,\t"); 
    break;
  }
  
  // Get clients coming from server
  BridgeClient client = server.accept();

  // There is a new client?
  if (client) {
    // Process request
    process(client);

    // Close connection and free resources.
    client.stop();
  }

  delay(200); //wait a while ;
}
void process(BridgeClient client) {
  // read the command
  String command = client.readStringUntil('/');
  client.println("Status: 200");
  client.println("Access-Control-Allow-Origin: *");   
  client.println("Access-Control-Allow-Methods: GET");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  // is "connect" command?
  if (command == "connect") {
    dataJson["status"] = "OK";
    dataJson.printTo(client);
  }
  // is "data" command?
  if (command == "data") {
     dataCommand(client);
  }
  // is "temperature" command?
  if (command == "temp") {
    tempCommand(client);
  }
  // is "humidity" command?
  if (command == "humidity") {
    humidityCommand(client);
  }
  // is "hall" command?
  if (command == "hall") {
    hallCommand(client);
  }
  // is "adc" command?
  if (command == "adc") {
    adcCommand(client);
  }
  // is "relay" command?
  if (command == "relay") {
    relayCommand(client);
  }
}
void dataCommand(BridgeClient client) {
    getTemp();
    getHumidity();
    getHall();
    getAdc();

    dataJson["moteId"] = MOTEID;
    dataJson["groupId"] = groupId;
    dataJson["temp"] = temp;
    dataJson["humidity"] = humidity;
    dataJson["hall"] = hall;
    dataJson["adc"] = adc;
    dataJson["relay"] = relay;
    // Send feedback to client
    dataJson.printTo(client);
}
void tempCommand(BridgeClient client) {
    getTemp();
    sensorJson["sensor"] = "temperature";
    sensorJson["value"] = temp;
    // Send feedback to client
    sensorJson.printTo(client);
    
    // Update datastore key with the current pin value
    String key = "A0";
    Bridge.put(key, String(temp));
}
void humidityCommand(BridgeClient client) {
    getHumidity();
    sensorJson["sensor"] = "humidity";
    sensorJson["value"] = humidity;
    // Send feedback to client
    sensorJson.printTo(client);
    
    // Update datastore key with the current pin value
    String key = "A1";
    Bridge.put(key, String(humidity));
}
void hallCommand(BridgeClient client) {
    getHall();
    sensorJson["sensor"] = "hall";
    sensorJson["value"] = hall;
    // Send feedback to client
    sensorJson.printTo(client);
    
    // Update datastore key with the current pin value
    String key = "A2";
    Bridge.put(key, String(hall));
}
void adcCommand(BridgeClient client) {
    getAdc();
    sensorJson["sensor"] = "adc";
    sensorJson["value"] = adc;
    // Send feedback to client
    sensorJson.printTo(client);
    
    // Update datastore key with the current pin value
    String key = "A3";
    Bridge.put(key, String(adc));
}
void relayCommand(BridgeClient client) {
    int value = client.parseInt();
    digitalWrite(relayPin, value);
    relay = value;
    sensorJson["sensor"] = "relay";
    sensorJson["value"] = value;
    // Send feedback to client
    sensorJson.printTo(client);
    
    // Update datastore key with the current pin value
    String key = "D8";
    Bridge.put(key, String(relayPin));
}
void getTemp() {
  // Get raw value of Temperature
  temp = analogRead(tempPin);
  Serial.print("Temp: ");
  Serial.println(temp);
   //read thermistor value 
  long a =1023 - temp;
  //the calculating formula of temperature
  float tempC = beta /(log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
  Serial.println(tempC);
}
void getHall() {
  // Get raw value of Hall Effect
  hall = analogRead(hallPin);
  Serial.print("Hall: ");
  Serial.println(hall);
}

void getHumidity() {
  // Get raw value of Humidity
  humidity = DHT.humidity;
  Serial.print("Humidity: ");
  Serial.println(humidity);
}
void getAdc() {
  // Get raw value of Humidity
  adc = analogRead(adcPin);
  Serial.print("Adc: ");
  Serial.println(adc);
}


