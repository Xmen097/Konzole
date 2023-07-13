#include "define.h"

#include <SPI.h>                    
#include <PDQ_GFX.h>
#include <PDQ_ILI9341.h>

#include <Fonts/FreeSerif12pt7b.h>
#include <Fonts/FreeSans12pt7b.h>

extern "C" char __data_start[];    // start of SRAM data
extern "C" char _end[];     // end of SRAM data (used to check amount of SRAM this program's variables use)
extern "C" char __data_load_end[];  // end of FLASH (used to check amount of Flash this program's code and data uses)

Display::Display(PDQ_ILI9341 *tft_n) {
  tft = tft_n;
}
Display::setup(uint8_t brightness) {
  #if defined(ILI9341_RST_PIN)  // reset like Adafruit does
    FastPin<ILI9341_RST_PIN>::setOutput();
    FastPin<ILI9341_RST_PIN>::hi();
    FastPin<ILI9341_RST_PIN>::lo();
    delay(1);
    FastPin<ILI9341_RST_PIN>::hi();
  #endif
  tft->begin();  
  tft->setRotation(1);
  analogWrite(ILI9341_LED_PIN, brightness);
}
Display::fillScreen(color_t color) {
  tft->fillScreen(color);
}
Display::fillRect(int x, int y, int w, int h, color_t color) {
  tft->fillRect(x, y, w, h, color);
}
Display::drawPixel(int x, int y, color_t color) {
  tft->drawPixel(x, y, color);
}
Display::println(char *s) {
  tft->println(s);
}
Display::print(char *s) {
  tft->print(s);
}
Display::println(__FlashStringHelper *s) {
  tft->println(s);
}
Display::print(__FlashStringHelper *s) {
  tft->print(s);
}
Display::setTextColor(color_t color) {
  tft->setTextColor(color);
}
Display::setTextSize(int size) {
  tft->setTextSize(size);
}
Display::setCursor(int x, int y) {
  tft->setCursor(x,y);
}
Display::drawLine(int x0, int y0, int x1, int y1, color_t color) {
  tft->drawLine(x0,y0,x1,y1,color);
}
Display::drawCircle(int x0, int y0, int r, color_t color) {
  tft->drawCircle(x0, y0, r, color);
}
Display::fillCircle(int x0, int y0, int r, color_t color) {
  tft->fillCircle(x0, y0, r, color);
}
Display::drawHLine(int x, int y, int d, color_t color) {
  tft->drawFastHLine(x, y, d, color);
}
Display::drawVLine(int x, int y, int d, color_t color) {
  tft->drawFastVLine(x, y, d, color);
}
Display::fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
  tft->fillTriangle(x0, y0, x1, y1, x2, y2, color);
}
Display::drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color) {
  tft->drawTriangle(x0, y0, x1, y1, x2, y2, color);
}
Display::fillRoundRect(int x, int y, int w, int h, int r, color_t color) {
  tft->fillRoundRect(x, y, w, h, r, color);
}
Display::setBrightness(uint8_t brightness) {
  analogWrite(ILI9341_LED_PIN, brightness);
}

PDQ_ILI9341 tft_driver;
Display tft(&tft_driver);
