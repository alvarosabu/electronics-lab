#define sensorPin A0
#define voltage 5 // Depends on the board, 5V or 3.3V
#define resolution 1023 // Arduino is a 10-bit ADC meaning it has the ability to detect 1,024 (2^10) discrete analog levels.

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int adc = analogRead(sensorPin);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float sensorValue = adc * (5.0 / resolution);
  // print out the value you read:
  Serial.println(sensorValue);
}
