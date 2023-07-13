#include "define.h"



namespace shooter {

  struct shot {
    int16_t x;
    int16_t y;
    int16_t row;
    bool active;
  };

  shot shots_buffer[10] = {};
  byte shot_pointer = 0;

  #define grid 32
  #define grid_width 10
  #define grid_height 6

  uint32_t row_time = 2000;
  uint32_t last_row_time=0;
  bool dead = false;
  uint16_t score = 0;

  color_t bg_color = color_black;
  
  const PROGMEM uint8_t LR[][5] = {{2,20,2,2,255},{4,18,2,2,255},{4,20,2,0,2},{6,16,2,2,255},{6,18,2,0,2},{8,14,2,2,255},{8,16,2,0,2},{8,22,2,6,255},{10,6,8,2,255},{10,14,2,1,2},{10,16,4,1,0},{10,20,2,5,0},{10,24,2,7,255},{12,2,4,1,255},{12,6,2,1,2},{12,8,2,3,2},{12,10,4,1,2},{12,22,2,5,6},{12,24,2,6,7},{12,26,2,7,255},{14,0,2,0,255},{14,2,4,0,1},{14,6,2,3,1},{14,8,2,4,3},{14,10,4,0,1},{14,16,4,0,1},{14,20,2,0,5},{14,26,2,6,7},{14,28,2,7,255},{16,0,2,255,0},{16,2,4,1,0},{16,6,2,1,3},{16,8,2,3,4},{16,10,4,1,0},{16,16,4,1,0},{16,20,2,5,0},{16,26,2,7,6},{16,28,2,255,7},{18,2,4,255,1},{18,6,2,2,1},{18,8,2,2,3},{18,10,4,2,1},{18,22,2,6,5},{18,24,2,7,6},{18,26,2,255,7},{20,6,8,255,2},{20,14,2,2,1},{20,16,4,0,1},{20,20,2,0,5},{20,24,2,255,7},{22,14,2,255,2},{22,16,2,2,0},{22,22,2,255,6},{24,16,2,255,2},{24,18,2,2,0},{26,18,2,255,2},{26,20,2,2,0},{28,20,2,255,2}};
  const PROGMEM uint8_t UD[0][5];
  const PROGMEM color_t colors[] = {44378,61279,50684,30202,19575,64880,61900,45255};
  Entity ship(LR, UD, colors, 58, 0);

  const PROGMEM uint8_t enemy_sprite[][5] = {{14,8,4,0,255},{12,10,2,0,255},{14,10,2,1,0},{16,10,2,2,0},{18,10,2,0,255},{10,12,2,0,255},{12,12,2,1,0},{14,12,2,2,1},{18,12,2,2,0},{20,12,2,0,255},{8,14,2,0,255},{10,14,2,1,0},{12,14,2,2,1},{20,14,2,2,0},{22,14,2,0,255},{6,16,2,3,255},{8,16,2,1,0},{10,16,2,2,1},{22,16,2,2,0},{24,16,2,3,255},{6,18,2,4,3},{8,18,2,3,1},{10,18,14,3,2},{24,18,2,4,3},{6,20,2,255,4},{8,20,16,4,3},{24,20,2,255,4},{8,22,16,255,4}};
  const PROGMEM color_t enemy_colors[] = {21273,63423,31902,33911,25393};

  color_t blue_colors[2] = {0x63FF, 0x19FF};
  color_t green_colors[2] = {0x0721, 0x0580};
  color_t orange_colors[2] = {0xFCE8, 0xDA80};
  color_t red_colors[2] = {0xFA28, 0xD800};
  color_t purple_colors[2] = {0xEA3F, 0xC01B};
  color_t lightblue_colors[2] = {0x471F, 0x05DB};
  color_t yellow_colors[2] = {0xFF90, 0xD600};
  color_t *color_schemes[] = {blue_colors, green_colors, orange_colors, red_colors, purple_colors, lightblue_colors, yellow_colors};
  uint8_t color_count = 7;
  
  uint8_t* enemyCounts = NULL;

  void death() {
    tft.fillScreen(color_red);
    tft.setTextSize(6);
    tft.setCursor(19,65);
    tft.setTextColor(color_white);
    tft.print(F("YOU LOSE"));
    tft.setTextSize(3);
    tft.setCursor(80,150);
    tft.print(F("Score:"));
    char score_text[3];
    itoa(score,score_text,10);
    tft.print(score_text);
    dead = true;
  }

  void update_shots() {
    for (int a=0; a<10; a++) {
      auto cur_shot = shots_buffer[a];
      if (not cur_shot.active) continue;
      tft.fillRect(cur_shot.x-1, cur_shot.y, 3, 8, bg_color);
      shots_buffer[a].y-=2;
      tft.fillRect(cur_shot.x-1, shots_buffer[a].y, 3, 8, color_red);
      if (enemyCounts[cur_shot.row]*grid-4 > cur_shot.y) {
        if (enemyCounts[cur_shot.row] != 0) {
          score++;
        }
        enemyCounts[cur_shot.row] = max(0, enemyCounts[cur_shot.row]-1);
        tft.fillRect(cur_shot.row*grid, (enemyCounts[cur_shot.row])*grid, grid, grid, bg_color);
        tft.fillRect(cur_shot.x-1, shots_buffer[a].y, 3, 8, bg_color);
        shots_buffer[a].active = false;
      }
    }
  }

  void shoot() {
    shot new_shot{ship.pos_x+14, 190, (ship.pos_x+14)/grid, true};
    shots_buffer[shot_pointer] = new_shot;
    shot_pointer = (shot_pointer+1)%10;
  }

  void draw_enemy(byte tile_x, byte tile_y) {
    int x = tile_x*grid;
    int y = tile_y*grid;
    tft.drawLine(x+6, y+17, x+15, y+8, 0x19FF);
    tft.drawLine(x+7, y+17, x+15, y+9, 0x19FF);
    tft.drawLine(x+25, y+17, x+16, y+9, 0x19FF);
    tft.drawLine(x+24, y+17, x+16, y+8, 0x19FF);
    tft.drawLine(x+8, y+17, x+15, y+10, color_white);
    tft.drawLine(x+9, y+17, x+16, y+10, color_white);
    tft.fillTriangle(x+10, y+17, x+16, y+11, x+22, y+17, 0x63FF);
    tft.fillRect(x+6, y+18, 20, 2, 25393);
    tft.fillRect(x+8, y+20, 16, 2, 33911);
  }

  void drop_row() {
    for (int i=0; i<grid_width; i++) {
      if (enemyCounts[i] == grid_height) {
        death();
        return;
      }
      draw_enemy(i, enemyCounts[i]);
      enemyCounts[i]++;
      
    }
  }

  void setup() {
    enemyCounts = new uint8_t [grid_width]{0};
    tft.fillScreen(bg_color);
    
    ship.setSize(32, 32);
    ship.setPosition(screen_width/2+16, 200);
    ship.draw();
    last_row_time = millis()-7500; // 2.5 secs to new row at the beggining  
    row_time = 2000;
    last_row_time=0;
    dead = false;
    score = 0;
  }

  void loop() {
    if (dead || game_paused) return;
    Direction dpad_dir = Input::dpad_direction();
    if (dpad_dir == direction_left) {
      ship.move_x(false);
      ship.move_x(false);
    } else if (dpad_dir == direction_right) {
      ship.move_x(true); 
      ship.move_x(true); 
    }
    if (millis() - last_row_time > row_time) {
      last_row_time = millis();
      drop_row();
      if (dead) return;
    }
    if (Input::is_just_pressed(button_down)) {
      shoot();
    }
    update_shots();
  }

  void destruct() {
    delete[] enemyCounts;
  }
  
}
