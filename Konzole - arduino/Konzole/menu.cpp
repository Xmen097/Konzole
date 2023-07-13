#include "define.h"

namespace menu {

  struct Item {
    uint8_t (*data)[5]; 
    byte length;
    color_t *colors;
    color_t background;
  };

  const PROGMEM uint8_t pacman_data[][5] = {{10,0,12,0,255},{6,2,4,0,255},{22,2,4,0,255},{4,4,2,0,255},{18,4,4,255,0},{26,4,2,0,255},{2,6,2,0,255},{28,6,2,0,255},{2,8,2,255,0},{18,8,4,0,255},{4,10,4,255,0},{30,10,2,0,255},{8,12,4,255,0},{12,14,4,255,0},{12,18,4,0,255},{8,20,4,0,255},{4,22,4,0,255},{30,22,2,255,0},{2,24,2,0,255},{2,26,2,255,0},{28,26,2,255,0},{4,28,2,255,0},{26,28,2,255,0},{6,30,4,255,0},{22,30,4,255,0},{10,32,12,255,0}};
  const PROGMEM color_t pacman_colors[] = {65285};   
  Item pacman {pacman_data, 26, pacman_colors, color_dark_purple};

  const PROGMEM uint8_t settings_data[][5] = {{8,4,1,0,255},{7,5,1,0,255},{8,5,1,1,0},{9,5,1,0,255},{22,5,3,0,255},{6,6,1,0,255},{7,6,1,1,0},{8,6,1,2,1},{9,6,1,2,0},{10,6,1,0,255},{21,6,1,0,255},{22,6,1,1,0},{23,6,2,2,0},{25,6,1,0,255},{5,7,1,0,255},{6,7,1,1,0},{7,7,1,2,1},{10,7,1,2,0},{11,7,1,0,255},{4,8,1,0,255},{5,8,1,1,0},{6,8,1,2,1},{11,8,1,2,0},{12,8,1,0,255},{3,9,1,0,255},{4,9,1,1,0},{5,9,1,2,1},{12,9,1,2,0},{13,9,1,0,255},{3,10,1,255,0},{4,10,1,0,1},{5,10,2,0,2},{7,10,1,1,2},{10,10,3,0,2},{13,10,1,255,0},{4,11,2,255,0},{11,11,2,255,0},{19,21,2,0,255},{26,21,2,0,255},{18,22,1,0,255},{19,22,1,1,0},{20,22,2,2,0},{22,22,1,2,1},{25,22,3,2,0},{28,22,1,0,255},{18,23,1,255,0},{19,23,1,0,1},{20,23,1,1,2},{27,23,1,0,2},{28,23,1,255,0},{19,24,1,255,0},{20,24,1,0,1},{21,24,1,1,2},{26,24,1,0,2},{27,24,1,255,0},{20,25,1,255,0},{21,25,1,0,1},{22,25,1,1,2},{25,25,1,0,2},{26,25,1,255,0},{6,26,1,255,0},{7,26,1,0,1},{8,26,2,0,2},{10,26,1,255,0},{21,26,1,255,0},{22,26,1,0,1},{23,26,1,1,2},{24,26,1,0,2},{25,26,1,255,0},{7,27,3,255,0},{22,27,1,255,0},{23,27,1,0,1},{24,27,1,255,0},{23,28,1,255,0}};
  const PROGMEM color_t settings_colors[] = {0,33808,40179};
  Item settings {settings_data, 74, settings_colors, color_white};
  
  const PROGMEM uint8_t tetris_data[][5] = {{8,1,5,0,255},{13,6,5,0,255},{17,7,1,1,0},{16,8,1,1,0},{15,9,1,1,0},{14,10,1,1,0},{8,11,5,255,0},{13,11,1,1,0},{13,16,5,255,1},{18,16,10,2,255},{27,17,1,3,2},{26,18,1,3,2},{25,19,1,3,2},{24,20,1,3,2},{3,21,10,4,255},{18,21,5,5,2},{23,21,1,3,2},{12,22,1,6,4},{22,22,1,7,5},{11,23,1,6,4},{21,23,1,7,5},{10,24,1,6,4},{20,24,1,7,5},{9,25,1,6,4},{19,25,1,7,5},{8,26,1,6,4},{13,26,5,5,255},{18,26,1,7,5},{23,26,5,7,3},{7,27,1,6,4},{17,27,1,7,5},{6,28,1,6,4},{16,28,1,7,5},{5,29,1,6,4},{15,29,1,7,5},{4,30,1,6,4},{14,30,1,7,5},{3,31,1,255,4},{4,31,9,255,6},{13,31,1,255,5},{14,31,14,255,7}};
  const PROGMEM color_t tetris_colors[] = {65224,64806,21823,9311,62842,47041,62357,40672};
  Item tetris {tetris_data, 41, tetris_colors, color_purple};
  
  const PROGMEM uint8_t snake_data[][5] = {{4,8,12,0,255},{6,10,8,1,0},{8,12,4,255,1},{22,14,8,0,255},{26,16,2,2,0},{0,18,4,0,255},{16,18,6,0,255},{26,18,2,0,2},{0,20,6,1,0},{14,20,16,1,0},{0,22,8,255,1},{12,22,18,255,1}};
  const PROGMEM color_t snake_colors[] = {64320,58048,0};
  Item snake {snake_data, 12, snake_colors, color_lime};
  
  const PROGMEM uint8_t shooter_data[][5] = {{24,2,1,0,255},{7,3,3,1,255},{24,3,1,2,0},{6,4,1,1,255},{7,4,1,3,1},{8,4,2,4,1},{10,4,1,1,255},{5,5,1,1,255},{6,5,1,3,1},{7,5,1,4,3},{10,5,1,4,1},{11,5,1,1,255},{24,5,1,5,2},{4,6,1,1,255},{5,6,1,3,1},{6,6,1,4,3},{11,6,1,4,1},{12,6,1,1,255},{24,6,1,255,5},{3,7,1,6,255},{4,7,1,3,1},{5,7,1,4,3},{12,7,1,4,1},{13,7,1,6,255},{4,8,1,6,3},{5,8,8,6,4},{3,9,1,7,6},{13,9,1,7,6},{3,10,1,255,7},{4,10,9,7,6},{13,10,1,255,7},{24,10,1,0,255},{4,11,9,255,7},{24,11,1,2,0},{24,13,1,5,2},{24,14,1,255,5},{24,17,1,8,255},{23,18,1,9,255},{25,18,1,9,255},{22,20,1,10,255},{24,20,1,11,8},{26,20,1,10,255},{23,21,1,11,9},{24,21,1,12,11},{25,21,1,11,9},{23,22,1,9,11},{24,22,1,8,12},{25,22,1,9,11},{21,24,1,10,255},{22,24,1,9,10},{24,24,1,9,8},{26,24,1,9,10},{27,24,1,10,255},{20,25,1,10,255},{21,25,1,8,10},{24,25,1,8,9},{27,25,1,8,10},{28,25,1,10,255},{19,26,1,10,255},{20,26,1,8,10},{28,26,1,8,10},{29,26,1,10,255},{18,27,1,10,255},{19,27,1,8,10},{22,27,2,0,9},{25,27,2,0,9},{29,27,1,8,10},{30,27,1,10,255},{18,28,1,255,10},{19,28,2,255,8},{21,28,1,2,8},{22,28,1,2,0},{24,28,1,0,8},{26,28,1,2,0},{27,28,1,2,8},{28,28,2,255,8},{30,28,1,255,10},{21,29,1,255,2},{22,29,1,5,2},{23,29,3,2,0},{26,29,1,5,2},{27,29,1,255,2},{22,30,1,255,5},{23,30,1,5,2},{25,30,1,5,2},{26,30,1,255,5},{23,31,1,255,5},{24,31,1,5,2},{25,31,1,255,5},{24,32,1,255,5}};
  const PROGMEM color_t shooter_colors[] = {64880,21273,61900,63423,31902,45255,33911,25393,44378,61279,50684,30202,19575,61309};
  Item shooter {shooter_data, 90, shooter_colors, color_black};
  
  const PROGMEM uint8_t mario_data[][5] = {{10,0,12,0,255},{8,2,2,0,255},{22,2,6,0,255},{8,4,8,1,0},{16,4,4,2,0},{20,4,2,3,0},{22,4,2,2,0},{24,4,4,255,0},{6,6,2,1,255},{10,6,2,2,1},{14,6,2,2,1},{24,6,4,2,255},{14,8,2,1,2},{20,8,2,2,3},{22,8,2,3,2},{28,8,2,2,255},{6,10,2,255,1},{10,10,2,1,2},{12,10,4,2,1},{20,10,2,3,2},{24,10,4,3,2},{28,10,2,255,2},{8,12,2,255,1},{10,12,2,2,1},{20,12,4,2,3},{24,12,4,255,3},{8,14,2,0,255},{10,14,4,0,2},{14,14,2,4,2},{16,14,8,0,2},{24,14,2,0,255},{6,16,2,0,255},{20,16,2,4,0},{26,16,2,0,255},{4,18,2,0,255},{16,18,4,4,0},{28,18,2,0,255},{4,20,6,2,0},{12,20,2,4,0},{14,20,2,5,4},{20,20,2,5,4},{22,20,2,4,0},{26,20,4,2,0},{10,22,2,2,0},{14,22,2,4,5},{20,22,2,4,5},{24,22,2,2,0},{10,24,2,4,2},{24,24,2,4,2},{4,26,4,255,2},{8,26,2,4,2},{16,26,2,255,4},{26,26,4,255,2},{6,28,2,1,255},{8,28,6,1,4},{14,28,2,255,4},{18,28,2,255,4},{20,28,6,1,4},{26,28,2,1,255},{4,30,2,1,255},{28,30,2,1,255},{4,32,10,255,1},{20,32,10,255,1}};
  const PROGMEM color_t mario_colors[] = {55616,29249,60867,8452,475,64711};
  Item mario {mario_data, 63, mario_colors, color_blue};

  const PROGMEM uint8_t pong_data[][5] = {{2,6,4,0,255},{26,6,4,0,255},{21,17,2,0,255},{21,19,2,255,0},{2,26,4,255,0},{26,26,4,255,0}};
  const PROGMEM color_t pong_colors[] = {61309};
  Item pong {pong_data, 6, pong_colors, color_blue};

  const byte icon_count = 6;
  const Item icons[] = {pacman, pong , snake, shooter, tetris, settings};

  uint8_t menu_position;
  uint8_t scroll_position;

  void drawScroll() {
    if(scroll_position != 0) {
      tft.fillTriangle(120, 55, 200, 55, 160, 35, color_gray);
      tft.fillTriangle(140, 50, 180, 50, 160, 40, color_white);
    } else {
      int i=35;
      uint8_t colBlue = 31 - i/8;
      uint8_t colGreen = 0 + i/4;
      uint8_t colRed = 0 + i/16;
      for (; i<=55; i++) {
        colBlue -= ((i % 8) == 0);
        colGreen += ((i % 4) == 0);
        colRed += ((i % 16) == 0);
        uint16_t color = ((uint16_t) (colRed & 0b00011111) << 11) + ((uint16_t)(colGreen & 0b00111111) << 5) + (colBlue & 0b00011111);
        tft.drawHLine(120, i, 81, color);
      }
    }
    if (scroll_position != icon_count-6) {
      tft.fillTriangle(120, 220, 200, 220, 160, 240, color_gray);
      tft.fillTriangle(140, 225, 180, 225, 160, 235, color_white);
    } else {
      int i=220;
      uint8_t colBlue = 31 - i/8;
      uint8_t colGreen = 0 + i/4;
      uint8_t colRed = 0 + i/16;
      for (; i<=240; i++) {
        colBlue -= ((i % 8) == 0);
        colGreen += ((i % 4) == 0);
        colRed += ((i % 16) == 0);
        uint16_t color = ((uint16_t) (colRed & 0b00011111) << 11) + ((uint16_t)(colGreen & 0b00111111) << 5) + (colBlue & 0b00011111);
        tft.drawHLine(120, i, 81, color);
      }
    }
  }
  
  void drawBatteryIcon() {
    const static PROGMEM byte row1[14] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11000000, 0b11000000, 0b11000000, 0b11000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000};
    const static PROGMEM byte row2[14] = {0b11111111, 0b11111111, 0b00000011, 0b00000011, 0b00000011, 0b00000011, 0b00000011, 0b10000011, 0b11000011, 0b01100011, 0b00000011, 0b00000011, 0b11111111, 0b11111111};
    const static PROGMEM byte row3[14] = {0b11111111, 0b11111111, 0b00000000, 0b00000000, 0b10001100, 0b11001110, 0b01101111, 0b00111101, 0b00011100, 0b00001100, 0b00000000, 0b00000000, 0b11111111, 0b11111111};
    const static PROGMEM byte row4[14] = {0b00111111, 0b00111111, 0b00110000, 0b00110000, 0b00110001, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b00110000, 0b00111111, 0b00111111};
    byte *rows[] = {row1, row2, row3, row4};
    for (byte r=0; r<4; r++) {
      for (byte i=0; i<14; i++) {
        byte data = pgm_read_byte_near(rows[r]+i);
        for (byte x=0; x<8; x++) {
          if (data&1<<x)
            tft.drawPixel(i+240,8*r+x-4, color_black);
        }
      }
    }
}

  void drawBackground() {
    uint8_t colBlue = 31;
    uint8_t colGreen = 0;
    uint8_t colRed = 0;
    for (int i = 0; i < 240; i++) {
      colBlue -= ((i % 8) == 0);
      colGreen += ((i % 4) == 0);
      colRed += ((i % 16) == 0);

      uint16_t color = ((uint16_t) (colRed & 0b00011111) << 11) + ((uint16_t)(colGreen & 0b00111111) << 5) + (colBlue & 0b00011111);
      tft.drawHLine(0, i, 320, color);
    }

    tft.fillRoundRect(0, -30, 320, 60, 30, color_white);
    tft.setCursor(96, 10);
    tft.setTextColor(color_black);
    tft.setTextSize(2);
    tft.print(F("Hlavni menu"));
    drawBatteryIcon();
  }

  void drawItem(int position) {
    int y = position/3;
    int x = position - y*3;
    if (position+scroll_position == menu_position) {
      tft.fillRoundRect(40+90*x, 65+85*y, 60, 60, 7, color_yellow);
    } else {
      tft.fillRoundRect(40+90*x, 65+85*y, 60, 60, 7, color_black);
    }
    tft.fillRoundRect(45+90*x, 70+85*y, 50, 50, 7, icons[position+scroll_position].background);
    draw_image(54+90*x, 79+85*y, icons[position+scroll_position].data, icons[position+scroll_position].length, icons[position+scroll_position].colors, 32, icons[position+scroll_position].background);
  }

  void drawItems() {
    for (int i=0; i<6; i++) {
      drawItem(i);
    }
  }

  void selectMenuItem() {
    current_game = menu_position+1;  
    game_setups[current_game]();
  }
  
  void setup() {
    menu_position = 0;
    scroll_position = 0;
    drawBackground();
    drawItems();
    drawScroll();
  }

  void destruct() {
    
  }

  void loop() {
    static byte last_battery = -2;
    byte new_battery = get_battery();
    if (last_battery != new_battery) {
      last_battery = new_battery;
      tft.fillRect(260, 0, 45, 24, color_white);
      tft.setCursor(260, 10);
      tft.setTextColor(color_black);
      tft.setTextSize(2);
      if (last_battery != 255) {
        char reading_text[3];
        itoa(last_battery,reading_text,10);
        tft.print(reading_text);
        tft.print("%");
      } else {
        tft.print("USB");
      }
    }
    if (Input::is_just_pressed(button_down)) {
      selectMenuItem();
    }
    if (Input::is_just_pressed(dpad_down) && menu_position+3 < icon_count) {
      menu_position += 3;
      if (menu_position >= scroll_position+6) {
        scroll_position+=3;
        drawScroll();
        drawItems();
      }
      drawItem(menu_position-3-scroll_position);
      drawItem(menu_position-scroll_position);
    }
    if (Input::is_just_pressed(dpad_up) && menu_position-3 >= 0) {
      menu_position -= 3;
      if (menu_position < scroll_position) {
        scroll_position-=3;
        drawScroll();
        drawItems();
      }
      drawItem(menu_position+3-scroll_position);
      drawItem(menu_position-scroll_position);
    }
    if (Input::is_just_pressed(dpad_left) && menu_position-1 >= 0) {
      menu_position -= 1;
      if (menu_position < scroll_position) {
        scroll_position-=3;
        drawScroll();
        drawItems();
      }
      drawItem(menu_position+1-scroll_position);
      drawItem(menu_position-scroll_position);
    }
    if (Input::is_just_pressed(dpad_right) && menu_position+1 < icon_count) {
      menu_position += 1;
      if (menu_position >= scroll_position+6) {
        scroll_position+=3;
        drawScroll();
        drawItems();
      }
      drawItem(menu_position-1-scroll_position);
      drawItem(menu_position-scroll_position);
    }
  }
}
