#include "define.h"

namespace tetris {

  int fall_time = 750;
  int colliding_times = 2;

  #define grid 16
  #define block_outline 2
  #define grid_width screen_width/grid    // 20
  #define grid_height screen_height/grid  // 15
  #define max_height 13

  color_t bg_color = color_black;

  uint16_t block1 = 0b1110000100110000;
  uint16_t block2 = 0b1110000110110000;
  uint16_t block3 = 0b1100000100100000;
  uint16_t block4 = 0b0111000000111000;
  uint16_t block5 = 0b0111000100110111;
  uint16_t block6 = 0b0111000010111000;
  uint16_t block7 = 0b0111000100111000;
  uint16_t block8 = 0b0111000001111000;
  uint16_t block9 = 0b0111000011110000;
  uint16_t block10= 0b0111000110011000;

  uint16_t blocks[] = {block1, block1, block2, block2, block3, block3, block4, block5, block6, block7, block8, block9, block10};
  uint8_t block_count = 13;

  color_t blue_colors[4] = {0x63FF, 0x4B3F, 0x19FF, 0x0015};
  color_t green_colors[4] = {0x0721, 0x0661, 0x0580, 0x0340};
  color_t orange_colors[4] = {0xFCE8, 0xFC85, 0xDA80, 0x9160};
  color_t red_colors[4] = {0xFA28, 0xF965, 0xD800, 0x9000};
  color_t purple_colors[4] = {0xEA3F, 0xE17E, 0xC01B, 0x8012};
  color_t lightblue_colors[4] = {0x471F, 0x2F1F, 0x05DB, 0x03F2};
  color_t yellow_colors[4] = {0xFF90, 0xFF44, 0xD600, 0x9400};
  color_t *color_schemes[] = {blue_colors, green_colors, orange_colors, red_colors, purple_colors, lightblue_colors, yellow_colors};
  uint8_t color_count = 7;
  

  uint8_t* fallenBlocks = NULL;
  uint8_t* fallenWidth = NULL;

  uint16_t curBlock;
  uint8_t curColor;
  int8_t curX;
  int8_t curY;

  bool dead;

  void draw(int x, int y, uint8_t color = curColor) {
    color_t *color_scheme = color_schemes[color]; 
    tft.fillRect(x*grid+block_outline, y*grid+block_outline, grid-2*block_outline, grid-2*block_outline, color_scheme[1]);
    tft.fillRect(x*grid+block_outline/2, y*grid, grid-block_outline, block_outline, color_scheme[0]);
    tft.fillRect(x*grid, y*grid+block_outline/2, block_outline, grid-block_outline, color_scheme[2]);
    tft.fillRect((x+1)*grid-block_outline, y*grid+block_outline/2, block_outline, grid-block_outline, color_scheme[2]);
    tft.fillRect(x*grid+block_outline/2, (y+1)*grid-block_outline, grid-block_outline, block_outline, color_scheme[3]);
  }
  
  void die() {
    tft.fillScreen(color_red);
    tft.setTextSize(6);
    tft.setCursor(19,95);
    tft.setTextColor(color_white);
    tft.print(F("YOU LOSE"));
    dead = true;
  }

  void draw_block() {
    bool determinant = curBlock & (1 << 15);
    for (uint8_t x=0; x<3-determinant; x++) {
      for (uint8_t y=0; y<3-determinant; y++) {
        bool pixel = curBlock & (1 << 8-x-3*y);
        if (pixel) {
          draw(curX+x, curY+y);
        } else if (fallenBlocks[curX+x + (curY+y)*grid_width] == 0) {
          tft.fillRect((curX+x)*grid, (curY+y)*grid, grid, grid, bg_color);
        }
      }
    }
  }

  void clear_row(uint8_t row) {
    for (int r=row-1; r>=0; r--) {
      fallenWidth[r+1] = fallenWidth[r];
      for (int i=0; i<grid_width; i++) {
        int pixel = fallenBlocks[r*grid_width + i];
        fallenBlocks[(r+1)*grid_width + i] = fallenBlocks[r*grid_width + i];
        if (pixel) {
          draw(i, r+1, pixel-1);
        } else {
          tft.fillRect(i*grid, (r+1)*grid, grid, grid, bg_color);
        }
      }
    }
  }

  void save_block() {
    bool determinant = curBlock & (1 << 15);
    for (uint8_t y=0; y<3-determinant; y++) {
      for (uint8_t x=0; x<3-determinant; x++) {
        bool pixel = curBlock & (1 << 8-x-3*y);
        if (pixel && (curX+x+(curY+y)*grid_width) <= (grid_height-max_height)*grid_width)
          die();
        if (pixel) {
          fallenBlocks[curX+x + (curY+y)*grid_width] = curColor+1;
          fallenWidth[curY+y] += 1;
          if (fallenWidth[curY+y] == grid_width) {
            clear_row(curY+y);
          }
        }
      }
    }
  }

  void generate_new_block() {
    curBlock = blocks[random(block_count)];
    curColor = random(color_count);
    curX = 9;
    curY = 0;
    draw_block();
  }

  bool will_collide(uint16_t block, int8_t blockX, int8_t blockY) {
    bool determinant = block & (1 << 15);
    for (int8_t x=0; x<3-determinant; x++) {
      for (int8_t y=0; y<3-determinant; y++) {
        bool pixel = block & (1 << 8-x-3*y);
        if (pixel && (blockY+y >= grid_height || fallenBlocks[blockX+x + (blockY+y)*grid_width]))
          return true;
        if (pixel && (blockX+x < 0 || blockX+x >= grid_width))
          return true;
      }
    }
    return false;
  }
  
  void move_block(Direction dir) {
    bool determinant = curBlock & (1 << 15);
    if (dir == direction_left && !will_collide(curBlock, curX-1, curY)) {
      curX--;
      for (int i=0; i<3-determinant; i++) {
        if (fallenBlocks[curX+3-determinant + (curY+i)*grid_width] == 0)
          tft.fillRect((curX+3-determinant)*grid, (curY+i)*grid, grid, grid, bg_color);
      }
      draw_block();
    } else if (dir == direction_right && !will_collide(curBlock, curX+1, curY)) {
      curX++;
      for (int i=0; i<3-determinant; i++) {
        if (fallenBlocks[curX-1 + (curY+i)*grid_width] == 0)
          tft.fillRect((curX-1)*grid, (curY+i)*grid, grid, grid, bg_color);
      }
      draw_block();
    } else if (dir == direction_down && !will_collide(curBlock, curX, curY+1)) {
      curY += 1;
      for (int i=0; i<3-determinant; i++) {
        if (fallenBlocks[curX+i + (curY-1)*grid_width] == 0)
          tft.fillRect((curX+i)*grid, (curY-1)*grid, grid, grid, bg_color);
      }
      draw_block();
    }
  }

  void rotate_block(int dir) {
    if (dir == 0) return;
    bool determinant = curBlock & (1 << 15);
    uint16_t temp = determinant * (1 << 15);
    for (uint8_t x=0; x<3-determinant; x++) {
      bool any = false;
      for (uint8_t y=0; y<3-determinant; y++) {
        bool pixel = ((curBlock >> (8-x-3*y))&1);
        temp |= pixel << (8-3*x-(2-determinant-y));
        if (pixel) any = true;
      }
      temp |= any << (14-x);
    }
    if (!will_collide(temp, curX, curY))
      curBlock = temp;
    draw_block();
  }

  
  void check_input() {
    const int move_time = 100;
    
    static unsigned long last_dir_time = millis();
    Direction dir = Input::dpad_direction();
    if ((dir == direction_left || dir == direction_right || dir == direction_down) && millis() - last_dir_time > move_time) {
      last_dir_time = millis();
      move_block(dir);
    }
    
    int rot = Input::is_just_pressed(button_right) - Input::is_just_pressed(button_left);
    static unsigned long last_rot_time = millis();
    if (rot != 0 && millis() - last_rot_time > move_time) {
      last_rot_time = millis();
      rotate_block(rot);
    }
  }

  void fall_down() {
    static unsigned long last_time = millis();
    static uint8_t colliding = 0;
    if (millis() - last_time > fall_time) {
      last_time = millis();
      if (will_collide(curBlock, curX, curY+1)) {
        colliding += 1;
      } else {
        colliding = 0;
        move_block(direction_down);
      }
    }
    if (colliding == colliding_times) {
      colliding = 0;
      save_block();
      if (!dead)
        generate_new_block();
    }
  }
  
  void setup() {
    dead = false;
    generate_new_block();
    fallenBlocks = new uint8_t [grid_width*grid_height]{};
    fallenWidth = new uint8_t [grid_height]{};
    tft.fillScreen(bg_color);
    draw_block();
  }
  
  void loop() {
    if (dead || game_paused) return;
    check_input();
    fall_down();
  }

  void destruct() {
    delete[] fallenBlocks;
    delete[] fallenWidth;
  }

  
}
