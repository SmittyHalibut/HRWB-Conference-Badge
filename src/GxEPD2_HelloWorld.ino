// GxEPD2_HelloWorld.ino by Jean-Marc Zingg

// see GxEPD2_wiring_examples.h for wiring suggestions and examples
// if you use a different wiring, you need to adapt the constructor parameters!

// uncomment next line to use class GFX of library GFX_Root instead of Adafruit_GFX
//#include <GFX.h>
#include <SPI.h>
#include <Wire.h>
//#include <GxEPD2_BW.h>
#include <GxEPD2_3C.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// select the display class and display driver class in the following file (new style):
//#include "GxEPD2_display_selection_new_style.h"

// or select the display constructor line in one of the following files (old style):
//#include "GxEPD2_display_selection.h"
//#include "GxEPD2_display_selection_added.h"

// alternately you can copy the constructor from GxEPD2_display_selection.h or GxEPD2_display_selection_added.h to here
// e.g. for Wemos D1 mini:
//GxEPD2_BW<GxEPD2_154_D67, GxEPD2_154_D67::HEIGHT> display(GxEPD2_154_D67(/*CS=D8*/ SS, /*DC=D3*/ 0, /*RST=D4*/ 2, /*BUSY=D2*/ 4)); // GDEH0154D67
//GxEPD2_DISPLAY_CLASS<GxEPD2_DRIVER_CLASS, MAX_HEIGHT(GxEPD2_DRIVER_CLASS)> display(GxEPD2_DRIVER_CLASS(/*CS=5*/ EPD_CS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

#define PIN_SPI_EINK_CS (39) // 2 -> 23 -> 36
#define PIN_SPI_MOSI (27)    // 27
#define PIN_SPI_MISO (19)    // 19
#define PIN_SPI_SCLK (18)    // 18
#define PIN_SPI_DC (12)      // 12
#define PIN_EINK_RST (13)    // 13
#define PIN_EINK_BUSY (38)   // 17 -> 38

GxEPD2_3C<GxEPD2_290c, GxEPD2_290c::HEIGHT> display(GxEPD2_290c(PIN_SPI_EINK_CS, PIN_SPI_DC, PIN_EINK_RST, PIN_EINK_BUSY));


void setup()
{
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);   // Turn off power to eInk
  Serial.begin(9600);
  delay(5000);
  SPI.begin(PIN_SPI_SCLK, -1, PIN_SPI_MOSI, PIN_SPI_EINK_CS);

  Serial.println("Powering up eInk display");
  digitalWrite(21, LOW);    // turn on eInk
  Serial.println("Waiting 5 seconds for it to wake up");
  delay(5000);

  Serial.println("display.init()");
  display.init(9600);

  Serial.println("display.helloWorld()");
  helloWorld();

  Serial.println("display.hibernate()");
  display.hibernate();

  Serial.println("Waiting a second");
  delay(1000);

  Serial.println("Powering down eInk display");
  digitalWrite(21, HIGH);  // Turn the eInk off again.
}

const char HelloWorld[] = "Hello World!";

void helloWorld()
{
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center the bounding box by transposition of the origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
}

void loop() {
  //Serial.println("Sleeping 5s...");
  delay(5000);
};
