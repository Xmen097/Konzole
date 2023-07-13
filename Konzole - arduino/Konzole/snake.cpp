#include "define.h"

// 2200 BYTES OF FLASH

// Code written in cooperation with Vojtech Cerny

namespace snake {
  #define grid 12 // Velikost políčka - musí být násobek 4
  #define maxLen (screen_width / grid) * (screen_height / grid)/2
  const int delayTime = 250;
  
  uint8_t *snake = NULL;
  int *head;
  int *prevHead;
  int *prevTail;
  int *apple;
  
  int snakeLen;
  bool eaten;
  bool dead;
  unsigned long prevTime;
  
  Direction dir;
  Direction lastDir;
  
  
  
  const color_t background = color_green;
  const color_t col_snake = color_blue;
  const color_t col_apple = color_red;

  byte move(Direction dir, int *part) {
    if(dir == direction_left) part[0]-=1;
    if(dir == direction_right) part[0]+=1;
    if(dir == direction_up) part[1]-=1;
    if(dir == direction_down) part[1]+=1;
  }

  void death() {
    tft.fillScreen(color_red);
    tft.setTextSize(6);
    tft.setCursor(19,65);
    tft.setTextColor(color_white);
    tft.print(F("YOU LOSE"));
    tft.setTextSize(3);
    tft.setCursor(100,160);
    tft.print(F("Score:"));
    char score_text[3];
    itoa(snakeLen-2,score_text,10);
    tft.print(score_text);
    dead = true;
  }
  
  void checkDeath() {
    if (head[0] < 0 || head[1] < 0 || head[0] >= screen_width / grid || head[1] >= screen_height / grid) {
      death();
    }
    int prevTailCopy[2];
    prevTailCopy[0] = prevTail[0];
    prevTailCopy[1] = prevTail[1];
    for (int i = 0; i < snakeLen - 1; i++) {
      move(snake[i], prevTailCopy);
      if (prevTailCopy[0] == head[0] && prevTailCopy[1] == head[1]) {
        death();
      }
    }
  }
  
  void updateSnake() {
    if (eaten) {
      eaten = false;
      snake[snakeLen] = snake[snakeLen - 1];
      snakeLen++;
    } else {
      move(snake[0], prevTail);
  
      tft.fillRect(prevTail[0] * grid, prevTail[1] * grid, grid, grid, background);
  
      for (int i = 0; i < snakeLen - 1; i++) {
        snake[i] = snake[i + 1];
      }
    }
    // ------------------------------- update head
    snake[snakeLen - 1] = dir;
    prevHead[0] = head[0];
    prevHead[1] = head[1];
    move(dir, head);
    // ------------------------------- draw head
    if (snakeLen == 1) {
      tft.fillRect(head[0] * grid + grid / 4, head[1] * grid + grid / 4, grid / 2, grid / 2, col_snake);
    } else if (prevHead[1] > head[1]) {
      tft.fillRect(head[0] * grid + grid / 4, head[1] * grid + grid / 4, grid / 2, grid, col_snake);
    } else if (prevHead[1] < head[1]) {
      tft.fillRect(head[0] * grid + grid / 4, head[1] * grid - grid / 4, grid / 2, grid, col_snake);
    } else if (prevHead[0] < head[0]) {
      tft.fillRect(head[0] * grid - grid / 4, head[1] * grid + grid / 4, grid, grid / 2, col_snake);
    } else if (prevHead[0] > head[0]) {
      tft.fillRect(head[0] * grid + grid / 4, head[1] * grid + grid / 4, grid, grid / 2, col_snake);
    }
  
    checkDeath();
  }
  
  void updateApple() {
    if (head[0] == apple[0] && head[1] == apple[1]) {
      eaten = true;
      int appleNewX = random(0, screen_width / grid);
      int appleNewY = random(0, screen_height / grid);
  
      int prevTailCopy[2];
      prevTailCopy[0] = prevTail[0];
      prevTailCopy[1] = prevTail[1];
      for (int i = 0; i < snakeLen; i++) {
        move(snake[i], prevTailCopy);
        if (prevTailCopy[0] == appleNewX && prevTailCopy[1] == appleNewY) {
          i = -1;
          appleNewX = random(0, screen_width / grid);
          appleNewY = random(0, screen_height / grid);
          prevTailCopy[0] = prevTail[0];
          prevTailCopy[1] = prevTail[1];
        }
      }
      apple[0] = appleNewX;
      apple[1] = appleNewY;
      tft.fillRect(apple[0] * grid + grid / 4, apple[1] * grid + grid / 4, grid / 2, grid / 2, col_apple);
    }
  }
  
  void setup() {
    snake = new uint8_t[maxLen];
    snake[0] = direction_right;
    snake[1] = direction_right;
  
    snakeLen = 2;
    eaten = false;
    dead = false;
  
    head = new int[2];
    prevHead = new int[2];
    prevTail = new int[2];
    apple = new int[2];

  
    int temp_head [2] = {7, 5};
    memcpy(head, temp_head, 4);
    int temp_prevHead[2] = {6, 5};
    memcpy(prevHead, temp_prevHead, 4);
    int temp_prevTail[2] = {5, 5};
    memcpy(prevTail, temp_prevTail, 4);
    prevTime = millis();
    
    dir = direction_right;
    lastDir = direction_right;
    
    int temp_apple[2] = {random(0, screen_width / grid), random(0, screen_height / grid)};
    memcpy(apple, temp_apple, 4);
    
    tft.fillScreen(background);
    tft.fillRect(apple[0] * grid + grid / 4, apple[1] * grid + grid / 4, grid / 2, grid / 2, col_apple);
  }
  
  void destruct() {
    delete[] snake;
    delete[] head;
    delete[] prevHead;
    delete[] prevTail;
    delete[] apple;
  }
  
  void loop() {
    if (dead || game_paused) return;
    unsigned long currentTime = millis();
    if (currentTime - prevTime >= delayTime) {
      prevTime = currentTime;
  
      updateSnake();
      updateApple();
  
      lastDir = dir;
    }
    
    if (Input::is_just_pressed(dpad_down) && !(lastDir == direction_up && snakeLen != 1)) {
      dir = direction_down;
    }
    if (Input::is_just_pressed(dpad_up) && !(lastDir == direction_down && snakeLen != 1)) {
      dir = direction_up;
    }
    if (Input::is_just_pressed(dpad_left) && !(lastDir == direction_right && snakeLen != 1)) {
      dir = direction_left;
    }
    if (Input::is_just_pressed(dpad_right) && !(lastDir == direction_left && snakeLen != 1)) {
      dir = direction_right;
    }
  }

}
