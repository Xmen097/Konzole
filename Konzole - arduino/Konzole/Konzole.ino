#include "define.h"
#include <EEPROM.h>

enum games:uint8_t {
  Menu, Pacman, Pong, Snake, Shooter, Tetris, Settings
};
void (*game_setups[])() = {menu::setup, pacman::setup, pong::setup, snake::setup, shooter::setup, tetris::setup, test::setup};
void (*game_loops[])() = {menu::loop, pacman::loop, pong::loop, snake::loop, shooter::loop, tetris::loop, test::loop};
void (*game_destructors[])() = {menu::destruct, pacman::destruct, pong::destruct, snake::destruct, shooter::destruct, tetris::destruct, test::destruct};


games current_game = Menu;
long bat_pointer = 0;
uint32_t timer = 0;

void setup() {
  tft.setup(255);
  Input::setup();
  Input::loop(); // to avoid false read during first loop
  game_setups[current_game]();
}
void loop() {
  Input::loop();
  sys_functions();
  game_loops[current_game]();
  frame_time_stabilizer();
}
