![repository-banner.png](https://res.cloudinary.com/alvarosaburido/image/upload/v1564929632/as-readme-banner_tqdgrx.png)

# YunSensorMote

>A Sensor Mote using [Arduino Yun](https://store.arduino.cc/arduino-yun) that comunicates via Wifi through REST calls using the Bridge Library.

It uses a [ArduinoJson](https://arduinojson.org/) library to return json objects with the raw data.

## The Circuit:
  * Arduino A0 connected to Vout signal pin of KY-013 Analog Temperature Sensor from [Keyes](https://tkkrlab.nl/wiki/Arduino_KY-013_Temperature_sensor_module).
  * Arduino A1 connected to Vout signal pin of KY-015 Humidity DHT11 Sensor from [Keyes](https://tkkrlab.nl/wiki/Arduino_KY-015_Temperature_and_humidity_sensor_module).
  * Arduino A2 connected to Vout signal pin of KY-18 LDR Sensor from [Keyes](https://tkkrlab.nl/wiki/Arduino_KY-018_Photo_resistor_module).
  * Arduino A3 connected to a 10K Pot that will simulate any other analog sensor.
  * Arduino D8 connected to KY-019 Relay Module [Keyes](https://tkkrlab.nl/wiki/Arduino_KY-019_5V_relay_module)
  * Arduino I2C SDA/SCL connected to Adafruit's [MPL3115A2](https://www.adafruit.com/product/1893) Sensor Module


  # Support, Questions, or Feedback
> Contact me anytime for anything about this repo or IoT in general

* [Email: Alvaro Saburido](alvaro.saburido@gmail.com)
* [Twitter: @alvarosaburido1](https://twitter.com/alvarosaburido1)

___

# License
 [MIT](/LICENSE)
