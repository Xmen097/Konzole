#include "define.h"

#define sample_count 10

namespace test {
  const byte axis[] = {axis_left1, axis_left2, axis_left3, axis_right1, axis_right2, axis_battery};

  int reading = 0;
  char reading_text[4];
  const __FlashStringHelper *names[6];
  
  void setup() {
    names[0] = F("L1");
    names[1] = F("L2");
    names[2] = F("L3");
    names[3] = F("R1");
    names[4] = F("R2");
    names[5] = F("BT");
    tft.setTextColor(color_white);
    tft.fillScreen(color_black);
    tft.setCursor(55, 20);
    tft.setTextSize(3);
    tft.println(F("Test konzole"));
    tft.setTextSize(2);
    tft.setCursor(150, 60);
    tft.print(F("osy"));
    tft.setTextColor(color_white);
    tft.setTextSize(1);
    for(byte a=0; a<6; a++) {
      tft.setCursor(0, 100+20*a);
      tft.print(F("Osa "));
      tft.print(names[a]);
      tft.print(F(":"));
    }
    delay(750);
  }
  
  void loop() {
    if (game_paused) return;
    for(byte a=0; a<6; a++) {
      reading = 0;
      for (byte i=0; i<sample_count; i++ ) {
        reading += analogRead(axis[a]);
      }
      itoa(reading/sample_count,reading_text,10);
      tft.setCursor(50, 100+20*a);
      tft.print(reading_text);
    }
    
    delay(100);
    tft.fillRect(50, 100, 25, 120, color_black);
  }

  void destruct(){};
  
}
