#include "define.h"

// 3350 BYTES OF FLASH

namespace pacman { 
  uint8_t *map_data = NULL;

  byte dots_remaining;
  bool game_running;
  Direction current_direction;
  Direction future_direction;
    
  const uint8_t horizontal_data[] = {0b00000000,0b11111111,0b00000000,0b00000000,0b00000000,0b00000000,0b11111111,0b00000000};
  const uint8_t vertical_data[] = {0b01000010,0b01000010,0b01000010,0b01000010,0b01000010,0b01000010,0b01000010,0b01000010};
  const uint8_t corner[] = {0b00000000, 0b00000011, 0b00001100, 0b00010000, 0b00100000, 0b00100000, 0b01000001, 0b01000010};
  const uint8_t end_V[] = {0b00000000, 0b00011111, 0b00100000, 0b01000000, 0b01000000, 0b00100000, 0b00011111, 0b00000000};
  const uint8_t end_H[] =  {0b00000000, 0b00011000, 0b00100100, 0b01000010, 0b01000010, 0b01000010, 0b01000010, 0b01000010};
  const uint8_t single_data[] = {0b00000000, 0b00111100, 0b01100110, 0b01000010, 0b01000010, 0b01100110, 0b00111100, 0b00000000};
  const uint8_t connection_H[] = {0b00000000, 0b11111111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b10000001, 0b01000010};
  const uint8_t connection_V[] = {0b01000010, 0b01000001, 0b01000000, 0b01000000, 0b01000000, 0b01000000, 0b01000001, 0b01000010};
  const uint8_t dot_data[] = {0b00000000, 0b00000000, 0b00011000, 0b00111100, 0b00111100, 0b00011000, 0b00000000, 0b00000000};
  Tile_8 horizontal(horizontal_data, 0x01FD);
  Tile_8 vertical(vertical_data, 0x01FD);
  Tile_8 corner_UL(corner, 0x01FD, false, false);
  Tile_8 corner_UR(corner, 0x01FD, false, true);
  Tile_8 corner_DL(corner, 0x01FD, true, false);
  Tile_8 corner_DR(corner, 0x01FD, true, true);
  Tile_8 end_VL(end_V, 0x01FD, false, false);
  Tile_8 end_VR(end_V, 0x01FD, false, true);
  Tile_8 end_HU(end_H, 0x01FD, false, false);
  Tile_8 end_HD(end_H, 0x01FD, true, false);
  Tile_8 single(single_data, 0x01FD, false, false);
  Tile_8 connection_HU(connection_H, 0x01FD, false, false);
  Tile_8 connection_HD(connection_H, 0x01FD, true, false);
  Tile_8 connection_VL(connection_V, 0x01FD, false, true);
  Tile_8 connection_VR(connection_V, 0x01FD, false, false);
  Tile_8 dot(dot_data, 0xFFFF, false, false);
  
  const PROGMEM uint8_t pacman_LR[][5] = {{1,3,1,0,255},{1,12,1,0,255},{2,2,1,0,255},{2,4,1,0,255},{2,11,1,0,255},{2,13,1,0,255},{3,1,1,0,255},{3,14,1,0,255},{4,5,1,0,255},{4,10,1,0,255},{5,0,1,0,255},{5,15,1,0,255},{6,6,1,0,255},{6,9,1,0,255},{8,7,2,0,255},{9,2,2,255,0},{11,0,1,255,0},{11,2,2,0,255},{11,15,1,255,0},{13,1,1,255,0},{13,14,1,255,0},{14,2,1,255,0},{14,13,1,255,0},{15,3,2,255,0},{15,11,2,255,0},{16,5,6,255,0}};
  const PROGMEM uint8_t pacman_UD[][5] = {{5,0,6,0,255},{3,1,2,0,255},{11,1,2,0,255},{2,2,1,0,255},{9,2,2,255,0},{13,2,1,0,255},{1,3,1,0,255},{14,3,1,0,255},{1,4,1,255,0},{9,4,2,0,255},{2,5,2,255,0},{15,5,1,0,255},{4,6,2,255,0},{6,7,2,255,0},{6,9,2,0,255},{4,10,2,0,255},{2,11,2,0,255},{15,11,1,255,0},{1,12,1,0,255},{1,13,1,255,0},{14,13,1,255,0},{2,14,1,255,0},{13,14,1,255,0},{3,15,2,255,0},{11,15,2,255,0},{5,16,6,255,0}};
  const PROGMEM color_t pacman_colors[] = {65285};
  Entity pacman(pacman_LR, pacman_UD, pacman_colors, 26, 26);
  
  void setup() {  
    uint8_t temp_map_data[] = {
      1,2,2,2,2,10,2,2,2,2,2,2,2,2,10,2,2,2,2,3,
      5,0,16,16,16,5,16,16,16,16,16,16,16,16,5,16,16,16,16,5,
      5,16,1,12,16,8,16,13,2,2,2,2,12,16,8,16,13,3,16,5,
      5,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,5,
      5,16,5,16,4,16,13,2,3,16,16,1,2,12,16,4,16,5,16,5,
      5,16,5,16,5,16,16,16,9,2,2,11,16,16,16,5,16,5,16,5,
      5,16,8,16,5,16,4,16,16,16,16,16,16,4,16,5,16,8,16,5,
      5,16,16,16,8,16,9,3,16,1,3,16,1,11,16,8,16,16,16,5,
      5,16,4,16,16,16,16,8,16,9,11,16,8,16,16,16,16,4,16,5,
      5,16,5,16,1,12,16,16,16,16,16,16,16,16,13,3,16,5,16,5,
      5,16,5,16,9,12,16,1,2,12,13,2,3,16,13,11,16,5,16,5,
      5,16,5,16,16,16,16,5,0,0,0,0,5,16,16,16,16,5,16,5,
      5,16,9,2,2,12,16,9,2,2,2,2,11,16,13,2,2,11,16,5,
      5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,
      9,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,11
    };
    map_data = temp_map_data;

    dots_remaining = 139;
    game_running = true;
    current_direction = direction_none;
    future_direction = direction_none;
  
    BG_solid cerne_pozadi(0x0000);
    Tile_8 tiles[] = {corner_UL, horizontal, corner_UR, end_HU, vertical, single, connection_VL, end_HD, corner_DL, connection_HU, corner_DR, end_VR, end_VL, connection_HD, connection_VR, dot};
    BG_tiled_16 mapa(tiles, map_data, 20, 15);
    cerne_pozadi.draw();
    mapa.draw();
    pacman.setSize(16, 16);
    pacman.setPosition(16, 16);
    pacman.draw();
  }
  
  void loop() {
    if (!game_running || game_paused) return;
    Direction dpad_dir = Input::dpad_direction();
    future_direction = dpad_dir != direction_none ? dpad_dir : future_direction;
    pacman.move(current_direction);
    byte pos_whole_x = pacman.pos_x / 16;
    byte pos_whole_y = pacman.pos_y / 16;
    if (pacman.pos_x - pos_whole_x*16 == 0 && pacman.pos_y - pos_whole_y*16 == 0) {
      if (map_data[pos_whole_x + pos_whole_y*20] == 16) {
        map_data[pos_whole_x + pos_whole_y*20] = 0;
        dots_remaining--;
        if (dots_remaining == 0) {
          tft.setTextSize(6);
          tft.setCursor(35,95);
          tft.setTextColor(color_white);
          tft.print(F("YOU WIN"));
          game_running = false;
          return;
        }
      }
      byte future_map_tile = map_data[pos_whole_x + (future_direction == direction_left ? -1 : (future_direction == direction_right ? 1 : 0)) +
           (pos_whole_y + (future_direction == direction_up   ? -1 : (future_direction == direction_down  ? 1 : 0))) * 20];
      byte current_map_tile = map_data[pos_whole_x + (current_direction == direction_left ? -1 : (current_direction == direction_right ? 1 : 0)) +
           (pos_whole_y + (current_direction == direction_up ? -1 : (current_direction == direction_down  ? 1 : 0))) * 20];
      if (future_direction != direction_none && (future_map_tile == 0 || future_map_tile == 16)) {
        current_direction = future_direction;
        future_direction = direction_none;
      } else if (current_direction != direction_none && current_map_tile != 0 && current_map_tile != 16) {
        current_direction = direction_none;
      }
    }
  }

  void destruct() {
    delete[] map_data;
  }
  
}
