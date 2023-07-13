
#include "define.h"

// 3000 BYTES OF FLASH

namespace pong {

  const PROGMEM uint8_t lever_data[][5] = {{2,0,12,0,255},{0,2,2,0,255},{2,2,12,1,0},{14,2,2,0,255},{2,4,12,0,1},{2,6,12,1,0},{0,8,2,255,0},{2,8,12,0,1},{14,8,2,255,0},{2,10,2,2,0},{4,10,2,3,0},{6,10,2,4,0},{8,10,2,5,0},{10,10,2,6,0},{12,10,2,7,0},{2,38,2,0,2},{4,38,2,0,3},{6,38,2,0,4},{8,38,2,0,5},{10,38,2,0,6},{12,38,2,0,7},{0,40,2,0,255},{2,40,12,1,0},{14,40,2,0,255},{2,42,12,0,1},{2,44,12,1,0},{0,46,2,255,0},{2,46,12,0,1},{14,46,2,255,0},{2,48,12,255,0}};
  const PROGMEM color_t lever_colors[] = {36115,44470,23608,19381,17202,15056,12877,10731};
  Entity player(None, lever_data, lever_colors, 0,30);
  Entity enemy(None, lever_data, lever_colors, 0,30);

  const PROGMEM uint8_t ball_UD[][5] = {{1,0,3,0,255},{4,0,1,1,255},{0,1,1,0,255},{2,1,2,1,0},{5,1,1,1,255},{1,2,1,1,0},{5,2,1,2,1},{0,4,1,1,0},{4,4,1,2,1},{0,5,1,255,1},{2,5,2,2,1},{5,5,1,255,2},{1,6,1,255,1},{2,6,3,255,2}};
  const PROGMEM uint8_t ball_LR[][5] = {{0,1,3,0,255},{0,4,1,1,255},{1,0,1,0,255},{1,2,2,1,0},{1,5,1,1,255},{2,1,1,1,0},{2,5,1,2,1},{4,0,1,1,0},{4,4,1,2,1},{5,0,1,255,1},{5,2,2,2,1},{5,5,1,255,2},{6,1,1,255,1},{6,2,3,255,2}};
  const PROGMEM color_t ball_colors[] = {50809,44470,21390};
  Entity ball(ball_LR, ball_UD, ball_colors, 14,14);

  unsigned int score_1;
  unsigned int score_2;

  BG_solid background(0x0000, 2, 20, 316, 219);
  
  void move_player() {
    if (Input::is_pressed(dpad_up) && !player.will_collide(&ball, direction_up) && !player.will_collide(&background, direction_up)) {
      player.move_y(false);
    }
    if (Input::is_pressed(dpad_down) && !player.will_collide(&ball, direction_down) && !player.will_collide(&background, direction_down)) {
      player.move_y(true);
    }
  }
  
  void update_score() {
    char buffer[3];
    tft.fillRect(22, 0, 35, 18, 0x0000);
    itoa(score_1,buffer,10);
    tft.setCursor(22, 0);
    tft.print(buffer);
    tft.fillRect(283, 0, 35, 18, 0x0000);
    itoa(score_2,buffer,10);
    tft.setCursor(283, 0);
    tft.print(buffer);
    
  }
  
  void respawn_ball() {
    update_score();
    ball.hide();
    ball.setPosition(160-3, 120-3);
    ball.setSpeed(100,0);
    ball.draw();
    delay(1000);
  }

  void bounce(Direction direction) {
    if (direction == direction_up || direction == direction_down)
      ball.setSpeed(ball.speed_x, ball.speed_y*-1);
    if (direction == direction_left || direction == direction_right)
      ball.setSpeed(ball.speed_x*-1, ball.speed_y);
  }

  void move_ball() {
    auto wall_collide = ball.will_collide(&background);
    bounce(wall_collide);
    if (wall_collide == direction_left) {
      score_2++;
      respawn_ball();
    }
    if (wall_collide == direction_right) {
      score_1++;
      respawn_ball();
    }
    auto player_collide = ball.will_collide(&player);
    if (player_collide != direction_none) {
      ball.setSpeed(100, map((ball.pos_y+ball.size_y/2)-(player.pos_y+player.size_y/2), -30, 30, -100, 100));
    }
    auto enemy_collide = ball.will_collide(&enemy);
    if (enemy_collide != direction_none) {
      ball.setSpeed(-100, map((ball.pos_y+ball.size_y/2)-(enemy.pos_y+enemy.size_y/2), -30, 30, -100, 100));
    }
    ball.move();
  }
  
  void move_enemy() {
    if (enemy.pos_y + enemy.size_y/2 > ball.pos_y + ball.size_y && enemy.will_collide(&ball, direction_up) == direction_none && enemy.will_collide(&background, direction_up) == direction_none) {
      enemy.move_y(false);
    } else if (enemy.will_collide(&ball, direction_down) == direction_none && enemy.will_collide(&background, direction_down) == direction_none){
      enemy.move_y(true);
    }
  }
  
  void setup() {
    score_1 = 0;
    score_2 = 0;
    background.draw();
    enemy.setSize(16, 48);
    player.setSize(16, 48);
    player.setPosition(20, -48);
    enemy.setPosition(300-16, -48);
    for (int i=0; i<96+48; i++) {
      player.move_y(true);
      enemy.move_y(true);
    }
    tft.drawHLine(0, 19, 320, color_white);
    tft.drawHLine(0, 239, 320, color_white);
    tft.drawVLine(0, 19, 240, color_white);
    tft.drawVLine(319, 19, 240, color_white);
    tft.setCursor(135, 0);
    tft.setTextSize(2);
    tft.setTextColor(color_white);
    tft.println(F("Pong"));
    update_score();
    respawn_ball();
    ball.setSize(6,6);
  }
  
  void loop() {
    if (game_paused) return;
    move_player();
    move_player();
    move_enemy();
    move_ball();
    move_ball();
    move_ball();
  }

  void destruct() {};
  
}
