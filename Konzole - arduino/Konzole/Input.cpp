#include "define.h"

#define diff(a,b) (a>=b ? a-b : b-a)


#define dpad_value_left 330
#define dpad_value_middle 0
#define dpad_value_right 590

#define buttons_value_left 356
#define buttons_value_middle 527
#define buttons_value_right 840


namespace Input {
  const byte input_axis[5] = {axis_left1, axis_left2, axis_left3, axis_right1, axis_right2}; 
  int axis_values[5] = {0};
  int prev_axis_values[5] = {0};
  bool button_down[14] = {false};
  bool prev_button_down[14] = {false};
  const byte bottom_buttons[] = {button_bottom1_pin, button_bottom2_pin, button_bottom3_pin, button_bottom4_pin};

  
  const long voltage_multiplier = 1023;
  const long axis_treshold = 40*voltage_multiplier;
  const int change_treshold = 20;
  
  void setup() {
    pinMode(button_bottom1_pin, INPUT_PULLUP);
    pinMode(button_bottom2_pin, INPUT_PULLUP);
    pinMode(button_bottom3_pin, INPUT_PULLUP);
    pinMode(button_bottom4_pin, INPUT_PULLUP);
    analogReference(INTERNAL);
  }
  
  int axis;
  int but;
  long voltage_value;
  
  void loop() {
    for (int i=0; i<14; i++) {
      prev_button_down[i] = button_down[i];
    }
    voltage_value = analogRead(axis_battery);
     for (axis=0; axis<3; axis++) {
      prev_axis_values[axis] = axis_values[axis];
      axis_values[axis] = analogRead(input_axis[axis]);
      if (diff(prev_axis_values[axis], axis_values[axis]) < change_treshold) {
        long adjusted_value = axis_values[axis] * voltage_multiplier;
        if (diff(adjusted_value, voltage_value*dpad_value_left) < axis_treshold) {
          button_down[axis*2] = true;
          button_down[axis*2+1] = false;
        } else if (diff(adjusted_value, voltage_value*dpad_value_right) < axis_treshold) {
          button_down[axis*2] = false;
          button_down[axis*2+1] = true;
        } else if (diff(adjusted_value, voltage_value*dpad_value_middle) < axis_treshold) {
          button_down[axis*2] = true;
          button_down[axis*2+1] = true;
        } else {
          button_down[axis*2] = false;
          button_down[axis*2+1] = false;
        }
      }
     }
     for (axis=3; axis<5; axis++) {
      prev_axis_values[axis] = axis_values[axis];
      axis_values[axis] = analogRead(input_axis[axis]);
      if (diff(prev_axis_values[axis], axis_values[axis]) < change_treshold) {
        long adjusted_value = axis_values[axis] * voltage_multiplier;
        if (diff(adjusted_value, voltage_value*buttons_value_left) < axis_treshold) {
          button_down[axis*2] = true;
          button_down[axis*2+1] = false;
        } else if (diff(adjusted_value, voltage_value*buttons_value_right) < axis_treshold) {
          button_down[axis*2] = false;
          button_down[axis*2+1] = true;
        } else if (diff(adjusted_value, voltage_value*buttons_value_middle) < axis_treshold) {
          button_down[axis*2] = true;
          button_down[axis*2+1] = true;
        } else {
          button_down[axis*2] = false;
          button_down[axis*2+1] = false;
        }
      }
     }
     for (but=0; but<4; but++) {
      button_down[10+but] = digitalRead(bottom_buttons[but]);
     }
  }
  
  bool is_pressed(input_type button) {
    return button_down[(byte)button];
  }
  bool is_just_pressed(input_type button) {
    return button_down[(byte)button] && !prev_button_down[(byte)button];
  }
  bool is_just_released(input_type button) {
    return !button_down[(byte)button] && prev_button_down[(byte)button];
  }
  Direction dpad_direction() {
    if (Input::is_pressed(dpad_right)) {
      return direction_right;
    }
      
    if (Input::is_pressed(dpad_down)) {
      return direction_down;
    }
      
    if (Input::is_pressed(dpad_left)) {
      return direction_left;
    }
      
    if (Input::is_pressed(dpad_up)) {
      return direction_up;
    }
    return direction_none;
  }
}
