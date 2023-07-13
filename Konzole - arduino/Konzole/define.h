#include <Arduino.h>
#include "pin_define.h"

//colors
#define color_black 0x0000
#define color_white 0xffff
#define color_blue 0x03bd
#define color_yellow 0xFF0C
#define color_light_blue 0x1e1e
#define color_lime 0x3702
#define color_green 0x3702
#define color_red 0xf881
#define color_gray 0x8430
#define color_purple 0x781F
#define color_dark_purple 0x2011


#define screen_height 240
#define screen_width 320
  
typedef uint16_t color_t;
class PDQ_ILI9341;
extern const PROGMEM uint8_t None[][5];

extern bool sys_functions_disabled;
extern bool game_paused;

bool button_debounced(int i);
int get_battery();
static inline int8_t sign(int val);
void draw_image(int pos_x, int pos_y, uint8_t (*data)[5], byte len, color_t *colors, byte size_y, color_t background);
extern const int bottom_button_count;
extern const int bottom_button_pins[];


enum games: uint8_t;
extern games current_game;
extern void (*game_setups[])();
extern void (*game_loops[])();

enum input_type {
  dpad_up,
  shake_sensor,
  dpad_down,
  dpad_right,
  dpad_left,
  dpad_click,
  button_up,
  button_down,
  button_left,
  button_right,
  button_menu,
  button_pause,
  button_brightness,
  button_volume,
};

enum Direction {
  direction_none,
  direction_up,
  direction_down,
  direction_left,
  direction_right,
};

class Display {
  public:
  Display(PDQ_ILI9341 *tft);
  setup(uint8_t brightness);
  fillScreen(color_t color);
  fillRect(int x, int y, int w, int h, color_t color);
  println(char *s);
  print(char *s);
  println(__FlashStringHelper *s);
  print(__FlashStringHelper *s);
  setTextColor(color_t color);
  setTextSize(int size);
  setCursor(int x, int y);
  drawCircle(int x0, int y0, int r, color_t color);
  fillCircle(int x0, int y0, int r, color_t color);
  drawPixel(int x, int y, color_t color);
  drawHLine(int x, int y, int d, color_t color);
  drawVLine(int x, int y, int d, color_t color);
  fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
  drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, color_t color);
  fillRoundRect(int x, int y, int w, int h, int r, color_t color);
  drawLine(int x0, int y0, int x1, int y1, color_t color);
  setBrightness(uint8_t brightness);

  const int width = 320;
  const int height = 240;
  private:
   PDQ_ILI9341 *tft;
};
extern Display tft;

class Entity;

class Collidable {
  public:
   virtual Direction collide(Entity *entity, Direction direction);
};

class Entity: public Collidable {
  public:  
    uint8_t (*LR_data)[5];
    uint8_t (*UD_data)[5];
    uint8_t LR_length;
    uint8_t UD_length;
    color_t *colors;
    uint8_t size_x;
    uint8_t size_y;
    int pos_x;
    int pos_y;
    int speed_x;
    int speed_y;
    Entity(uint8_t (*LR_data)[5], uint8_t (*UD_data)[5], color_t *colors, uint8_t LR_length, uint8_t UD_length);
    setSize(uint8_t size_x, uint8_t size_y);
    setPosition(int pos_x, int pos_y);
    setSpeed(int speed_x, int speed_y);
    move(Direction dir);
    move_stable(Direction dir);
    move();
    move(uint8_t count);
    Direction move_and_collide(Collidable *collidable);
    Direction will_collide(Collidable *collidable);
    Direction will_collide(Collidable *collidable, Direction direction);
    Direction collide(Entity *entity, Direction direction);
    draw(bool mirror_v, bool mirror_h, bool rotate);
    draw();
    hide();
    move_x(bool direction);
    move_y(bool direction);
    move_x(bool direction, bool mirror_v, bool mirror_h, bool rotate);
    move_y(bool direction, bool mirror_v, bool mirror_h, bool rotate);
    Direction next_move();
  private:
    bool current_mirror_v;
    bool current_mirror_h;
    bool current_rotate;
    unsigned long moved_x;
    unsigned long moved_y;
    _move_x(bool direction, bool mirror_v, bool mirror_h, bool rotate);
    _move_y(bool direction, bool mirror_v, bool mirror_h, bool rotate);
    _draw(bool mirror_v, bool mirror_h, bool rotate);
};

class Tile_8 {
  public:
  color_t color;
  uint8_t *data;
  bool h_invert;
  bool v_invert;
  uint8_t size_x;
  uint8_t size_y;
  uint8_t get_row(uint8_t row);
  Tile_8(uint8_t *data, color_t color, bool h_invert=false, bool v_invert=false);
  draw(int x, int y);
  draw_2x(int x, int y);
  bool pixel_data(uint8_t x, uint8_t y);
};

class Background: public Collidable {
  public:
    draw();
    Direction collide(Entity *entity, Direction direction);
    color_t pixel_color(int x, int y);
};

class BG_solid : public Background {
  public:
    color_t color;
    BG_solid(color_t color);
    BG_solid(color_t color, int x, int y, int w, int h);
    draw();
    Direction collide(Entity *entity, Direction direction);
  private:
    int x1 = 0;
    int y1 = 0;
    int x2 = 320;
    int y2 = 240;
};

class BG_tiled_8 : public Background {
  public:
    uint8_t *data;
    Tile_8 *tiles;
    uint8_t size_x;
    uint8_t size_y;
    BG_tiled_8(Tile_8 *tiles, uint8_t *data, uint8_t size_x, uint8_t size_y);
    draw();
    Direction collide(Entity *entity,Direction direction);
};

class BG_tiled_16 : public Background {
  public:
    uint8_t *data;
    Tile_8 *tiles;
    uint8_t size_x;
    uint8_t size_y;
    BG_tiled_16(Tile_8 *tiles, uint8_t *data, uint8_t size_x, uint8_t size_y);
    draw();
    Direction collide(Entity *entity,Direction direction);
};

namespace pacman {
  void setup();
  void loop();
  void destruct();
}

namespace menu {
  void setup();
  void loop();
  void destruct();
}

namespace test {
  void setup();
  void loop();
  void destruct();
};

namespace pong {
  void setup();
  void loop();
  void destruct();
};

namespace snake {
  void setup();
  void loop();
  void destruct();
};

namespace shooter {
  void setup();
  void loop();
  void destruct();
};

namespace tetris {
  void setup();
  void loop();
  void destruct();
};

namespace Input {
  void setup();
  void loop();
  bool is_pressed(input_type button);
  bool is_just_pressed(input_type button);
  bool is_just_released(input_type button);
  Direction dpad_direction();
}
