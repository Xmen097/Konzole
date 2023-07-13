#include "define.h"

Direction Collidable::collide(Entity *entity, Direction direction) {
  return direction_none;
}

BG_solid::BG_solid(color_t color_n) {
  color = color_n;
}
BG_solid::BG_solid(color_t color_n, int x, int y, int w, int h) {
  color = color_n;
  x1 = x;
  y1 = y;
  x2 = x1+w;
  y2 = y1+h;
}

BG_solid::draw() {
  tft.fillScreen(color);
}

Direction BG_solid::collide(Entity *entity, Direction direction) {
  int8_t delta_x = direction == direction_left ? -1 : (direction == direction_right ? 1 : 0);
  int8_t delta_y = direction == direction_up ? -1 : (direction == direction_down ? 1 : 0);
  if (entity->pos_x+delta_x < x1) {
    return direction_left;
  }
  if (entity->pos_y+delta_y < y1) {
    return direction_up;
  }
  if (entity->pos_x+entity->size_x+delta_x > x2) {
    return direction_right;
  }
  if (entity->pos_y+entity->size_y+delta_y > y2) {
    return direction_down;
  }
  return direction_none;
}

BG_tiled_8::BG_tiled_8(Tile_8 *tiles_n, uint8_t *data_n, uint8_t size_x_n, uint8_t size_y_n) {
  tiles = tiles_n;
  size_x = size_x_n;
  size_y = size_y_n;
  data = data_n;
}

BG_tiled_8::draw() {
  for(int a=0; a<size_y; a++) {
    for(int b=0; b<size_x; b++) {
      uint8_t tile = data[a*size_x + b];
      if (tile != 0) {
        tiles[tile-1].draw(b*8, a*8);
      }
    }
  }
}

BG_tiled_16::BG_tiled_16(Tile_8 *tiles_n, uint8_t *data_n, uint8_t size_x_n, uint8_t size_y_n) {
  tiles = tiles_n;
  size_x = size_x_n;
  size_y = size_y_n;
  data = data_n;
}

BG_tiled_16::draw() {
  for(int a=0; a<size_y; a++) {
    for(int b=0; b<size_x; b++) {
      uint8_t tile = data[a*size_x + b];
      if (tile != 0) {
        tiles[tile-1].draw_2x(b*8, a*8);
      }
    }
  }
}
