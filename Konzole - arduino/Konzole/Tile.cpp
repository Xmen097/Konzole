#include "define.h"

const uint8_t shift_table[] = {0b10000000, 0b01000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001};

Tile_8::Tile_8(uint8_t *data_n, color_t color_n, bool h_invert_n=false, bool v_invert_n=false) {
  h_invert = h_invert_n;
  v_invert = v_invert_n;
  data = data_n;
  color = color_n;
}
Tile_8::draw_2x(int x, int y) {
  for(int b=0; b<8; b++) {
    uint8_t row = data[b];
    for(int a=7; a>=0; a--) {
      if (row&(1<<a)) {
        int pos1 = v_invert ? x+a : x+7-a;
        int pos2 = h_invert ? y+7-b : y+b;
        tft.fillRect(2*pos1, 2*pos2, 2, 2, color);
      }
    }
  }
}
uint8_t Tile_8::get_row(uint8_t row) {
  return data[row];
}
bool Tile_8::pixel_data(uint8_t x, uint8_t y) {
  return data[h_invert ? 7-y : y]&shift_table[v_invert ? 7-x : x];
}
