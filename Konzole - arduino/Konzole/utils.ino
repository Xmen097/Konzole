const PROGMEM uint8_t None[][5] = {};  // empty array for Entities

const int bottom_button_count = 4;
const int bottom_button_pins[] = {button_bottom1_pin, button_bottom2_pin, button_bottom3_pin, button_bottom4_pin};

uint16_t brightness = 255;

bool game_paused = false;

int input_debounce = 50; // set according to specific button
bool dbc_last_button_states[bottom_button_count] = {HIGH};
bool dbc_last_button_times[bottom_button_count] = {-1};

bool sys_functions_disabled;

//input device state was stable for at least button_debounce time.
bool button_debounced(int i) { return (millis() - dbc_last_button_times[i] > input_debounce); }

unsigned long last_frame_start = 0;
const int desired_frame_time = 10;

static inline int8_t sign(int val) {
  if (val < 0) return -1;
  if (val==0) return 0;
  return 1;
}

void debounce_update() {  //update debounce vars
  bool reading;
  for (int i=0; i<bottom_button_count; i++) {
    reading = digitalRead(bottom_button_pins[i]);
    if (reading != dbc_last_button_states[i]) {
      dbc_last_button_times[i] = millis(); 
      dbc_last_button_states[i] = reading;
    }
  }
}

void frame_time_stabilizer() {
  int wait_time = desired_frame_time - (millis() - last_frame_start);
  if (wait_time > 0)
    delay(wait_time);
  last_frame_start = millis();
}

void draw_image(int pos_x, int pos_y, uint8_t (*data)[5], uint8_t len, color_t *colors, byte size_y, color_t background) {
  for(int c=size_y; c>0; c--) {
    for(int i=0; i<len; i++) {
      uint8_t color_id = pgm_read_byte(&data[i][4]);
      color_t draw_color = color_id != 255 ? pgm_read_word_near(&colors[color_id]) : background;
      int y = pgm_read_byte(&data[i][1]) - c;
      if (y >= 0)
        tft.drawHLine(pos_x + pgm_read_byte(&data[i][0]), pos_y + y, pgm_read_byte(&data[i][2]), draw_color);
    }
  }
}

void sys_functions() {
  if (sys_functions_disabled) return;
  
  if (Input::is_just_pressed(button_menu)) {
    if (current_game == Menu) return;
    game_paused = false;
    game_destructors[current_game]();
    current_game = Menu;
    game_setups[Menu]();
  }
  if (Input::is_just_pressed(button_brightness)) {
    brightness = (brightness+64)%256;
    analogWrite(ILI9341_LED_PIN, brightness);
  }
  if (Input::is_just_pressed(button_pause)) {
    if (current_game == Menu) return;
    game_paused = !game_paused;
  }
}


int calculate_percent(float val) {
  val = max(400.0, val);
  const float deg4 = 2.109000e-7;
  const float deg3 = -4.486504e-4;
  const float deg2 = 3.534408e-1;
  const float deg1 = -1.217095e2;
  const float deg0 = 1.5447787e4;
  float result = deg4*val*val*val*val + deg3*val*val*val + deg2*val*val + deg1*val + deg0;
  return result;
}

int get_battery() {
  static uint32_t sum = 0;
  static uint32_t res = 0;
  static uint32_t last_value = -1;

  uint32_t mod = 1000L;

  if (sum == 0) {
    for (int i=0; i<mod; i++) {
      delayMicroseconds(500);
      sum += analogRead(axis_battery);
    }
  }
  
  uint32_t value = analogRead(axis_battery);

  sum -= sum/mod;
  sum += value;

  const uint32_t treshold = 500;
  
  if ((res*mod > sum && res*mod - sum > treshold) || (res*mod < sum && sum - res*mod > treshold)) {
    res = sum/mod;
    last_value = round(calculate_percent(res-256));
  }
  if (last_value > 101) {
    return -1;
  } else {
    return min(100, last_value);
  }
}
