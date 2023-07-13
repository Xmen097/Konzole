#include "define.h"

Entity::Entity(uint8_t (*LR_data_n)[5], uint8_t (*UD_data_n)[5], color_t *colors_n, uint8_t LR_length_n, uint8_t UD_length_n) {
    colors = colors_n;
    LR_data = LR_data_n;
    LR_length = LR_length_n;
    UD_data = UD_data_n;
    UD_length = UD_length_n;
    
}

Entity::setSize(uint8_t size_x_n, uint8_t size_y_n) {
  size_x = size_x_n;
  size_y = size_y_n;
}

Entity::setPosition(int pos_x_n, int pos_y_n) {
  pos_x = pos_x_n;
  pos_y = pos_y_n;
}
Entity::setSpeed(int speed_x_n, int speed_y_n) {
  moved_x = 0;
  moved_y = 0;
  speed_x = speed_x_n;
  speed_y = speed_y_n;
}

Entity::_draw(bool mirror_v, bool mirror_h, bool rotate) {
  current_mirror_v = mirror_v;
  current_mirror_h = mirror_h;
  current_rotate = rotate;
  tft.fillRect(pos_x, pos_y, size_x, size_y, 0x0000);
  for(int c=size_x; c>0; c--) {
    if (rotate) {
      for(int i=0; i<UD_length; i++) {
        uint8_t color_id = !mirror_v ? pgm_read_byte(&UD_data[i][3]) : pgm_read_byte(&UD_data[i][4]);
        color_t draw_color = color_id != 255 ? pgm_read_word_near(&colors[color_id]) : 0x0000;
        int x = (mirror_v ? pgm_read_byte(&UD_data[i][1]) : size_x - pgm_read_byte(&UD_data[i][1])) - c;
        int y = (mirror_h ? size_y - pgm_read_byte(&UD_data[i][0]) - pgm_read_byte(&UD_data[i][2]) : pgm_read_byte(&UD_data[i][0]));
        if (x >=0 and y >= 0)
          tft.drawVLine(pos_x + x, pos_y + y, pgm_read_byte(&UD_data[i][2]), draw_color);
      }
    } else {
      for(int i=0; i<LR_length; i++) {
        uint8_t color_id = !mirror_v ? pgm_read_byte(&LR_data[i][4]) : pgm_read_byte(&LR_data[i][3]);
        color_t draw_color = color_id != 255 ? pgm_read_word_near(&colors[color_id]) : 0x0000;
        int x = (mirror_v ? size_x - pgm_read_byte(&LR_data[i][0]) : pgm_read_byte(&LR_data[i][0])) - c;
        int y = (mirror_h ? size_y - pgm_read_byte(&LR_data[i][1])- pgm_read_byte(&LR_data[i][2]) : pgm_read_byte(&LR_data[i][1]));
        if (x >=0 and y >= 0)
          tft.drawVLine(pos_x + x, pos_y + y, pgm_read_byte(&LR_data[i][2]), draw_color);
      }
    }
  }
}

Entity::draw(bool mirror_v, bool mirror_h, bool rotate) {
  _draw(mirror_v, mirror_h, rotate);
}
Entity::draw() {
  _draw(false,false,false);
}

Entity::hide() {
  tft.fillRect(pos_x, pos_y, size_x, size_y, 0x0000);
}

Entity::_move_x(bool dir, bool mirror_v, bool mirror_h, bool rotate) {
  if (rotate) {
    for(int i=0; i<UD_length; i++) {
      uint8_t color_id = dir!=mirror_v ? pgm_read_byte(&UD_data[i][3]) : pgm_read_byte(&UD_data[i][4]);
      color_t draw_color = color_id != 255 ? pgm_read_word_near(&colors[color_id]) : 0x0000;
      int x = (mirror_v ? pgm_read_byte(&UD_data[i][1]) : size_x - pgm_read_byte(&UD_data[i][1])) - (dir ? 0 : 1);
      int y = (mirror_h ? size_y - pgm_read_byte(&UD_data[i][0]) - pgm_read_byte(&UD_data[i][2]) : pgm_read_byte(&UD_data[i][0]));
      tft.drawVLine(pos_x + x, pos_y + y, pgm_read_byte(&UD_data[i][2]), draw_color);
    }
  } else {
    for(int i=0; i<LR_length; i++) {
      uint8_t color_id = dir!=mirror_v ? pgm_read_byte(&LR_data[i][4]) : pgm_read_byte(&LR_data[i][3]);
      color_t draw_color = color_id != 255 ? pgm_read_word_near(&colors[color_id]) : 0x0000;
      int x = (mirror_v ? size_x - pgm_read_byte(&LR_data[i][0]) : pgm_read_byte(&LR_data[i][0])) - (dir ? 0 : 1);
      int y = (mirror_h ? size_y - pgm_read_byte(&LR_data[i][1]) - pgm_read_byte(&LR_data[i][2]) : pgm_read_byte(&LR_data[i][1]));
      tft.drawVLine(pos_x + x, pos_y + y, pgm_read_byte(&LR_data[i][2]), draw_color);
    }
  }
  pos_x += dir ? 1 : -1;
}
Entity::_move_y(bool dir, bool mirror_v, bool mirror_h, bool rotate) {
  if (rotate) {
    for(int i=0; i<LR_length; i++) {
      uint8_t color_id = dir!=mirror_h!=rotate ? pgm_read_byte(&LR_data[i][3]) : pgm_read_byte(&LR_data[i][4]);
      color_t draw_color = color_id != 255 ? pgm_read_word_near(&colors[color_id]) : 0x0000;
      int x = (mirror_v ? pgm_read_byte(&LR_data[i][1]) : size_x-pgm_read_byte(&LR_data[i][1]) - pgm_read_byte(&LR_data[i][2]));
      int y = (mirror_h ? size_y - pgm_read_byte(&LR_data[i][0]) : pgm_read_byte(&LR_data[i][0])) - (dir ? 0 : 1);
      tft.drawHLine(pos_x + x, pos_y + y, pgm_read_byte(&LR_data[i][2]), draw_color);
    }
  } else {
    for(int i=0; i<UD_length; i++) {
      uint8_t color_id = dir!=mirror_h ? pgm_read_byte(&UD_data[i][4]) : pgm_read_byte(&UD_data[i][3]);
      color_t draw_color = color_id != 255 ? pgm_read_word_near(&colors[color_id]) : 0x0000;
      int x = (mirror_v ? size_x-pgm_read_byte(&UD_data[i][0])-pgm_read_byte(&UD_data[i][2]) : pgm_read_byte(&UD_data[i][0]));
      int y = (mirror_h ? size_y - pgm_read_byte(&UD_data[i][1]) : pgm_read_byte(&UD_data[i][1])) - (dir ? 0 : 1);
      tft.drawHLine(pos_x + x, pos_y + y, pgm_read_byte(&UD_data[i][2]), draw_color);
    }
  }
  pos_y += dir ? 1 : -1;
}

Entity::move_x(bool direction) {
  _move_x(direction, current_mirror_v, current_mirror_h, current_rotate);
}
Entity::move_y(bool direction) {
  _move_y(direction, current_mirror_v, current_mirror_h, current_rotate);
}
Entity::move_x(bool direction, bool mirror_v, bool mirror_h, bool rotate) {
  if (current_mirror_v != mirror_v || current_mirror_h != mirror_h || current_rotate != rotate)
    draw(mirror_v, mirror_h, rotate);
  _move_x(direction, current_mirror_v, current_mirror_h, current_rotate);
}
Entity::move_y(bool direction, bool mirror_v, bool mirror_h, bool rotate) {
  if (current_mirror_v != mirror_v || current_mirror_h != mirror_h || current_rotate != rotate)
    draw(mirror_v, mirror_h, rotate);
  _move_y(direction, current_mirror_v, current_mirror_h, current_rotate);
}

Entity::move(Direction dir) {
  switch (dir) {
    case direction_right:
      move_x(true, true, false, false);
      break;
    case direction_down:
      move_y(true, false, true, true);
      break;
    case direction_left:
      move_x(false, false, false, false);
      break;
    case direction_up:
      move_y(false, true, false, true);
      break;
  }
}

Entity::move_stable(Direction dir) {
  switch (dir) {
    case direction_right:
      move_x(true, false, false, false);
      break;
    case direction_down:
      move_y(true, false, false, false);
      break;
    case direction_left:
      move_x(false, false, false, false);
      break;
    case direction_up:
      move_y(false, false, false, false);
      break;
  }
}

Entity::move() {
  if (moved_x*abs(speed_y) <= moved_y*abs(speed_x)) {
    moved_x++;
    move_x((speed_x > 0));
  } else {
    moved_y++;
    move_y((speed_y > 0));
  }
}

Direction Entity::next_move() {
  if (moved_x*abs(speed_y) < moved_y*abs(speed_x)) {
    return speed_x > 0 ? direction_right : direction_left;
  } else {
    return speed_y > 0 ? direction_down : direction_up;
  }
}

Entity::move(uint8_t count) {
  for(int i=0; i<count; i++)
    move();
}

Direction Entity::collide(Entity *entity, Direction direction) {
  int8_t delta_x = direction == direction_left ? -1 : (direction == direction_right ? 1 : 0);
  int8_t delta_y = direction == direction_up ? -1 : (direction == direction_down ? 1 : 0);
  if (entity->pos_x+delta_x < pos_x+size_x && entity->pos_x+delta_x > pos_x && entity->pos_y <= pos_y+size_y && entity->pos_y+entity->size_y >= pos_y) {
    return direction_left;
  }
  if (entity->pos_y+delta_y < pos_y+size_y && entity->pos_y+delta_y > pos_y && entity->pos_x <= pos_x+size_x && entity->pos_x+entity->size_x >= pos_x) {
    return direction_up;
  }
  if (entity->pos_x+entity->size_x+delta_x > pos_x && entity->pos_x+entity->size_x+delta_x < pos_x+size_x && entity->pos_y <= pos_y+size_y && entity->pos_y+entity->size_y >= pos_y) {
    return direction_right;
  }
  if (entity->pos_y+entity->size_y+delta_y > pos_y && entity->pos_y+entity->size_y+delta_y < pos_y + size_y && entity->pos_x <= pos_x+size_x && entity->pos_x+entity->size_x >= pos_x) {
    return direction_down;
  }
  return direction_none;
}

Direction Entity::move_and_collide(Collidable *collidable) {
  auto collision_result = will_collide(collidable);
  if (collision_result == direction_none)
    move();
  return collision_result;
}

Direction Entity::will_collide(Collidable *collidable) {
  return (*collidable).collide(this, next_move());
}

Direction Entity::will_collide(Collidable *collidable, Direction direction) {
  return (*collidable).collide(this, direction);
}
