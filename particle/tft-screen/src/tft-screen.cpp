/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "/Users/alvarosaburido/as/electronics/electronics-lab/Particle/tft-screen/src/tft-screen.ino"
#include <Adafruit_GFX_RK.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

void setup();
void loop();
void testDrawText(char *text, uint16_t color, int size);
void writeText(char *text);
#line 5 "/Users/alvarosaburido/as/electronics/electronics-lab/Particle/tft-screen/src/tft-screen.ino"
#define CS   A2
#define DC   D6
#define RST  -1

Adafruit_ST7735 tft = Adafruit_ST7735(CS, DC, RST);

void setup() {
  delay(1000);
  // Put initialization like pinMode and begin functions here.
  tft.initR(INITR_BLACKTAB); //for the ST7735R, otherwise would be initB for the B version
  Particle.function("Text", writeText);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  // The core of your code will likely live here.
}

void testDrawText(char *text, uint16_t color, int size)  {
  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(0, 0);
  tft.setTextColor(color);
  tft.setTextSize(size);
  tft.setTextWrap(true);
  tft.print(text);
}

void writeText(char *text) {
  testDrawText(text, ST7735_ORANGE, 2);
}
