/*
 * Project subscribe-event
 * Description:
 * Author:
 * Date:
 */
LEDStatus blinkError(RGB_COLOR_RED, LED_PATTERN_BLINK, LED_SPEED_NORMAL, LED_PRIORITY_IMPORTANT);

// setup() runs once, when the device is first turned on.
void setup() {
  // Put initialization like pinMode and begin functions here.
  Particle.subscribe("low-battery", onLowBattery, MY_DEVICES);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.

}

void onLowBattery(const char *event, const char *data) {
  blinkError.setActive(true);
  delay(3000);
  blinkError.setActive(false);
}
