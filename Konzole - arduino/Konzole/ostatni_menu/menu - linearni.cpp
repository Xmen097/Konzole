#include "define.h"

namespace menu {

  struct Item {
    uint8_t (*data)[5]; 
    byte length;
    color_t *colors;
    color_t background;
    char *name;
  };
  const PROGMEM uint8_t pacman_data[][5] = {{10,0,12,0,255},{6,2,4,0,255},{22,2,4,0,255},{4,4,2,0,255},{18,4,4,255,0},{26,4,2,0,255},{2,6,2,0,255},{28,6,2,0,255},{2,8,2,255,0},{18,8,4,0,255},{4,10,4,255,0},{30,10,2,0,255},{8,12,4,255,0},{12,14,4,255,0},{12,18,4,0,255},{8,20,4,0,255},{4,22,4,0,255},{30,22,2,255,0},{2,24,2,0,255},{2,26,2,255,0},{28,26,2,255,0},{4,28,2,255,0},{26,28,2,255,0},{6,30,4,255,0},{22,30,4,255,0},{10,32,12,255,0}};
  const PROGMEM color_t pacman_colors[] = {65285};   
  const PROGMEM char pacman_name[] = "pacman"; 
  Item pacman {pacman_data, 26, pacman_colors, color_dark_purple, pacman_name};

  const PROGMEM uint8_t settings_data[][5] = {{14,2,4,0,255},{6,4,4,0,255},{12,4,2,0,255},{14,4,4,1,0},{18,4,2,0,255},{22,4,4,0,255},{4,6,2,0,255},{6,6,2,2,0},{8,6,2,1,0},{10,6,2,0,255},{12,6,2,1,0},{18,6,2,1,0},{20,6,2,0,255},{22,6,4,1,0},{26,6,2,0,255},{10,8,2,1,0},{20,8,2,1,0},{4,10,2,255,0},{6,10,2,0,2},{8,10,2,2,1},{24,10,2,0,1},{26,10,2,255,0},{4,12,2,0,255},{6,12,2,2,0},{8,12,2,1,2},{14,12,4,0,1},{24,12,2,1,0},{26,12,2,0,255},{2,14,2,0,255},{4,14,2,2,0},{6,14,2,1,2},{12,14,2,0,1},{14,14,4,255,0},{18,14,2,0,1},{26,14,2,1,0},{28,14,2,0,255},{2,18,2,255,0},{4,18,2,0,2},{6,18,2,2,1},{12,18,2,1,0},{14,18,4,0,255},{18,18,2,1,0},{26,18,2,0,1},{28,18,2,255,0},{4,20,2,255,0},{6,20,2,0,2},{14,20,4,1,0},{24,20,2,0,1},{26,20,2,255,0},{4,22,2,0,255},{6,22,2,2,0},{20,22,2,2,1},{24,22,2,1,0},{26,22,2,0,255},{8,24,2,2,1},{10,24,2,0,1},{12,24,2,2,1},{18,24,2,2,1},{20,24,2,0,2},{22,24,4,2,1},{4,26,2,255,0},{6,26,4,0,2},{10,26,2,255,0},{12,26,2,0,2},{14,26,4,2,1},{18,26,2,0,2},{20,26,2,255,0},{22,26,4,0,2},{26,26,2,255,0},{6,28,4,255,0},{12,28,2,255,0},{14,28,4,0,2},{18,28,2,255,0},{22,28,4,255,0},{14,30,4,255,0}};
  const PROGMEM color_t settings_colors[] = {0,40179,33808};
  const PROGMEM char settings_name[] = "settings"; 
  Item settings {settings_data, 75, settings_colors, color_white, settings_name};
  
  const PROGMEM uint8_t tetris_data[][5] = {{8,1,5,0,255},{13,6,5,0,255},{17,7,1,1,0},{16,8,1,1,0},{15,9,1,1,0},{14,10,1,1,0},{8,11,5,255,0},{13,11,1,1,0},{13,16,5,255,1},{18,16,10,2,255},{27,17,1,3,2},{26,18,1,3,2},{25,19,1,3,2},{24,20,1,3,2},{3,21,10,4,255},{18,21,5,5,2},{23,21,1,3,2},{12,22,1,6,4},{22,22,1,7,5},{11,23,1,6,4},{21,23,1,7,5},{10,24,1,6,4},{20,24,1,7,5},{9,25,1,6,4},{19,25,1,7,5},{8,26,1,6,4},{13,26,5,5,255},{18,26,1,7,5},{23,26,5,7,3},{7,27,1,6,4},{17,27,1,7,5},{6,28,1,6,4},{16,28,1,7,5},{5,29,1,6,4},{15,29,1,7,5},{4,30,1,6,4},{14,30,1,7,5},{3,31,1,255,4},{4,31,9,255,6},{13,31,1,255,5},{14,31,14,255,7}};
  const PROGMEM color_t tetris_colors[] = {65224,64806,21823,9311,62842,47041,62357,40672};
  const PROGMEM char tetris_name[] = "tetris"; 
  Item tetris {tetris_data, 41, tetris_colors, color_purple, tetris_name};
  
  const PROGMEM uint8_t snake_data[][5] = {{4,8,12,0,255},{6,10,8,1,0},{8,12,4,255,1},{22,14,8,0,255},{26,16,2,2,0},{0,18,4,0,255},{16,18,6,0,255},{26,18,2,0,2},{0,20,6,1,0},{14,20,16,1,0},{0,22,8,255,1},{12,22,18,255,1}};
  const PROGMEM color_t snake_colors[] = {64320,58048,0};
  const PROGMEM char snake_name[] = "snake"; 
  Item snake {snake_data, 12, snake_colors, color_lime, snake_name};
  
  const PROGMEM uint8_t atari_data[][5] = {{2,3,6,0,255},{8,3,2,1,255},{12,3,6,0,255},{18,3,2,1,255},{22,3,6,0,255},{28,3,2,1,255},{6,4,2,1,0},{16,4,2,1,0},{26,4,2,1,0},{4,5,2,1,0},{14,5,2,1,0},{24,5,2,1,0},{2,6,2,1,0},{12,6,2,1,0},{22,6,2,1,0},{2,7,8,255,1},{12,7,8,255,1},{22,7,8,255,1},{2,10,6,0,255},{8,10,2,1,255},{12,10,6,0,255},{18,10,2,1,255},{22,10,6,0,255},{28,10,2,1,255},{6,11,2,1,0},{16,11,2,1,0},{26,11,2,1,0},{4,12,2,1,0},{14,12,2,1,0},{24,12,2,1,0},{2,13,2,1,0},{12,13,2,1,0},{22,13,2,1,0},{2,14,8,255,1},{12,14,8,255,1},{22,14,8,255,1},{3,15,3,2,255},{9,15,3,3,255},{14,15,3,2,255},{8,16,1,3,255},{9,16,3,4,3},{12,16,1,3,255},{17,16,2,2,255},{3,17,3,255,2},{14,17,2,255,2},{5,18,2,2,255},{16,18,3,255,2},{4,19,1,2,255},{8,19,1,255,3},{9,19,3,3,4},{12,19,1,255,3},{3,20,1,2,255},{6,20,1,255,2},{9,20,3,255,3},{5,21,1,255,2},{3,22,2,255,2}};
  const PROGMEM color_t atari_colors[] = {63878,49184,65535,0,31959};
  const PROGMEM char atari_name[] = "breakout"; 
  Item atari {atari_data, 56, atari_colors, color_gray, atari_name};
  
  const PROGMEM uint8_t mario_data[][5] = {{10,0,12,0,255},{8,2,2,0,255},{22,2,6,0,255},{8,4,8,1,0},{16,4,4,2,0},{20,4,2,3,0},{22,4,2,2,0},{24,4,4,255,0},{6,6,2,1,255},{10,6,2,2,1},{14,6,2,2,1},{24,6,4,2,255},{14,8,2,1,2},{20,8,2,2,3},{22,8,2,3,2},{28,8,2,2,255},{6,10,2,255,1},{10,10,2,1,2},{12,10,4,2,1},{20,10,2,3,2},{24,10,4,3,2},{28,10,2,255,2},{8,12,2,255,1},{10,12,2,2,1},{20,12,4,2,3},{24,12,4,255,3},{8,14,2,0,255},{10,14,4,0,2},{14,14,2,4,2},{16,14,8,0,2},{24,14,2,0,255},{6,16,2,0,255},{20,16,2,4,0},{26,16,2,0,255},{4,18,2,0,255},{16,18,4,4,0},{28,18,2,0,255},{4,20,6,2,0},{12,20,2,4,0},{14,20,2,5,4},{20,20,2,5,4},{22,20,2,4,0},{26,20,4,2,0},{10,22,2,2,0},{14,22,2,4,5},{20,22,2,4,5},{24,22,2,2,0},{10,24,2,4,2},{24,24,2,4,2},{4,26,4,255,2},{8,26,2,4,2},{16,26,2,255,4},{26,26,4,255,2},{6,28,2,1,255},{8,28,6,1,4},{14,28,2,255,4},{18,28,2,255,4},{20,28,6,1,4},{26,28,2,1,255},{4,30,2,1,255},{28,30,2,1,255},{4,32,10,255,1},{20,32,10,255,1}};
  const PROGMEM color_t mario_colors[] = {55616,29249,60867,8452,475,64711};
  const PROGMEM char mario_name[] = "mario"; 
  Item mario {mario_data, 63, mario_colors, color_blue, mario_name};

  const PROGMEM uint8_t pong_data[][5] = {{1,4,1,0,255},{2,4,1,1,255},{3,4,4,2,255},{25,4,1,0,255},{26,4,1,1,255},{27,4,4,2,255},{0,5,1,0,255},{1,5,1,3,0},{2,5,1,4,1},{3,5,4,4,2},{7,5,1,2,255},{24,5,1,0,255},{25,5,1,3,0},{26,5,1,4,1},{27,5,4,4,2},{31,5,1,2,255},{0,6,1,5,0},{1,6,1,2,3},{2,6,5,2,4},{7,6,1,6,2},{24,6,1,5,0},{25,6,1,2,3},{26,6,5,2,4},{31,6,1,6,2},{1,7,4,4,2},{5,7,1,7,2},{6,7,1,8,2},{25,7,4,4,2},{29,7,1,7,2},{30,7,1,8,2},{0,8,1,255,5},{1,8,1,9,4},{2,8,1,10,4},{3,8,1,11,4},{4,8,1,12,4},{5,8,1,13,7},{6,8,1,14,8},{7,8,1,255,6},{24,8,1,255,5},{25,8,1,9,4},{26,8,1,10,4},{27,8,1,11,4},{28,8,1,12,4},{29,8,1,13,7},{30,8,1,14,8},{31,8,1,255,6},{1,9,1,15,9},{2,9,1,16,10},{3,9,1,17,11},{4,9,1,18,12},{5,9,1,19,13},{6,9,1,20,14},{25,9,1,15,9},{26,9,1,16,10},{27,9,1,17,11},{28,9,1,18,12},{29,9,1,19,13},{30,9,1,20,14},{21,16,1,21,255},{22,16,1,8,255},{20,17,1,21,255},{21,17,1,8,21},{23,17,1,4,255},{20,19,1,255,21},{21,19,2,4,8},{23,19,1,255,4},{21,20,2,255,4},{1,23,1,9,15},{2,23,1,10,16},{3,23,1,11,17},{4,23,1,12,18},{5,23,1,13,19},{6,23,1,14,20},{25,23,1,9,15},{26,23,1,10,16},{27,23,1,11,17},{28,23,1,12,18},{29,23,1,13,19},{30,23,1,14,20},{0,24,1,6,255},{1,24,1,8,9},{2,24,1,22,10},{3,24,1,4,11},{4,24,1,4,12},{5,24,1,4,13},{6,24,1,4,14},{7,24,1,5,255},{24,24,1,6,255},{25,24,1,8,9},{26,24,1,22,10},{27,24,1,4,11},{28,24,1,4,12},{29,24,1,4,13},{30,24,1,4,14},{31,24,1,5,255},{1,25,1,2,8},{2,25,1,2,22},{3,25,4,2,4},{25,25,1,2,8},{26,25,1,2,22},{27,25,4,2,4},{0,26,1,2,6},{1,26,5,4,2},{6,26,1,3,2},{7,26,1,0,5},{24,26,1,2,6},{25,26,5,4,2},{30,26,1,3,2},{31,26,1,0,5},{0,27,1,255,2},{1,27,4,2,4},{5,27,1,1,4},{6,27,1,0,3},{7,27,1,255,0},{24,27,1,255,2},{25,27,4,2,4},{29,27,1,1,4},{30,27,1,0,3},{31,27,1,255,0},{1,28,4,255,2},{5,28,1,255,1},{6,28,1,255,0},{25,28,4,255,2},{29,28,1,255,1},{30,28,1,255,0}};
  const PROGMEM color_t pong_colors[] = {34002,36083,38196,42357,44470,36115,40277,44503,50809,27765,25651,25586,23505,23440,21327,23608,19381,17202,15056,12877,10731,61309,46615};
  const PROGMEM char pong_name[] = "pong"; 
  Item pong {pong_data, 125, pong_colors, color_blue, pong_name};

  const byte icon_count = 9; // celkovy pocet ikonek
  const Item icons[] = {pacman, pong ,settings , snake, atari, mario, tetris, snake, settings};

  uint8_t menu_position = 0;
  uint8_t scroll_position = 0;

  const uint8_t visible_count = 2; // pocet viditelnych radku/policek


  // renderovnani ukazatele scrolovani
  void drawScroll() {
    if(scroll_position != 0) {  //vyrenderovani horniho ukazatele scrolovani
      tft.fillTriangle(120, 55, 200, 55, 160, 35, color_gray);
      tft.fillTriangle(140, 50, 180, 50, 160, 40, color_white);
    } else {
      tft.fillTriangle(120, 55, 200, 55, 160, 35, color_light_blue); // smazani ukazatele scrolovani
    }
    if (scroll_position != icon_count-visible_count) { // dolni ukazatel scrollovani
      tft.fillTriangle(120, 220, 200, 220, 160, 240, color_gray);
      tft.fillTriangle(140, 225, 180, 225, 160, 235, color_white);
    } else {
      tft.fillTriangle(120, 220, 200, 220, 160, 240, color_light_blue); // smazani
    }
  }

  void drawBackground() { // vykreslime pozadi - vsechno co se nebude menit a nejsou to polozky v menu
    tft.fillScreen(color_light_blue);
    tft.setCursor(96, 10);
    tft.setTextSize(2);
    tft.print("Hlavni menu");
  }

  void drawItem(int position) {
  	uint8_t icon_pos = position+scroll_position;
    if (position+scroll_position == menu_position) {  // Je aktualni polozka vybrana
      tft.fillRoundRect(130, 65+85*position, 60, 60, 7, color_yellow);  // co vyrenderovat pokud je vybrana
    } else {
      tft.fillRoundRect(130, 65+85*position, 60, 60, 7, color_black);  // co vyrenderovat pokud neni vybrana
    }
    //zbytek vykreslení ikonky
    tft.fillRoundRect(135, 70+85*position, 50, 50, 7, icons[icon_pos].background);
    draw_image(144, 79+85*position, icons[icon_pos].data, icons[icon_pos].length, icons[icon_pos].colors, 32, icons[icon_pos].background);
  }

  void drawItems() { // vykreslime polozky v menu
    for (int i=0; i<visible_count; i++) {
      drawItem(i);
    }
  }

  void selectMenuItem() { // vybral jsem položku v menu - spustit odpovídající hru
    current_game = menu_position+1;  
    game_setups[current_game]();
  }
  
  void setup() {
    drawBackground();
    drawItems();
    drawScroll();
  }

  void loop() {
    if (Input::is_just_pressed(button_down)) { // vybrat položku v menu
      selectMenuItem();
    }
    if (Input::is_just_pressed(dpad_up) && menu_position-1 >= 0) { // vyber polozky v menu nahore
      menu_position -= 1;
      if (menu_position < scroll_position) { // menu potrebuje scrollovat
        scroll_position-=1;
        drawScroll();
        drawItems();
      } else { // scrollovat nemusíme, jen updatujeme vybrané/odvybrané  ikonky
        drawItem(menu_position+1-scroll_position);
        drawItem(menu_position-scroll_position);
      }
    }
    if (Input::is_just_pressed(dpad_down) && menu_position+1 < icon_count) {  // vyber polozky v menu dole
      menu_position += 1;
      if (menu_position >= scroll_position+visible_count) { // menu potrebuje scrollovat
        scroll_position+=1;
        drawScroll();
        drawItems();
      } else {  // scrollovat nemusíme, jen updatujeme vybrané/odvybrané  ikonky
        drawItem(menu_position-1-scroll_position);
        drawItem(menu_position-scroll_position);
      }
    }
  }

}
