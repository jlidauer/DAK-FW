/*
    DAK - is a firmware for Double Action Keyboards
    source.c - includes all functions used in the main loop.

    Copyright (C) 2017  Jaakob Lidauer

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


void read_switches() {
  long unsigned int time_current =  micros() / 100; //-> * 0.1 ms
  for (int c = 0; c < COLUMNS; c++) {
    //set one column active (HIGH)
    digitalWrite(COLUMN_PINS[c], HIGH);

    for (int r = 0; r < ROWS; r++) {
      uint8_t pin_state = digitalRead(ROW_PINS[r]);

      if (states[r][c].switch_bounce_time != 0 && time_current - states[r][c].switch_bounce_time >= DELAY_TIME_BOUNCE) { //If the switch is in a constant state -> add the change to the states array.
        states[r][c].state = pin_state;
        states[r][c].switch_bounce_time = 0;
        states[r][c].switch_state_changed_time = millis();
      }
      //set time:
      if (pin_state != states[r][c].state && states[r][c].switch_bounce_time == 0) {//State of the switch has changed for the first time.
        states[r][c].switch_bounce_time = time_current;
      } else if (pin_state == states[r][c].state && states[r][c].switch_bounce_time != 0) {//The state of the switch is not definite -> reset bounce timer
        states[r][c].switch_bounce_time = 0;
      }
    }
    digitalWrite(COLUMN_PINS[c], LOW);
  }
  
#ifdef DEBUG_PRINT_STATES_ARRAY
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLUMNS; c++) {
      Serial.print(states[r][c].state);
      Serial.print("\t");
    }
    Serial.println("");
  }
  Serial.println("************************************************************");
  delay(100);
#endif
}

void send_keys() {
  for (uint8_t i = 0; i < NUMBER_OF_KEYS; i++) {
    if (keys[i].type == SINGLE_ACTION || keys[i].type == SINGLE_ACTION_MODIFIER) {
      process_single_action_key(i);
    } else if (keys[i].type == DOUBLE_ACTION) {
      process_double_action_key(i);
    } else if (keys[i].type == DOUBLE_ACTION_NO_DELAY) {
      process_double_action_key_no_delay(i);
    }
  }
}

void process_single_action_key(uint8_t i) {
  uint8_t c = keys[i].first_switch_pos.c;
  uint8_t r = keys[i].first_switch_pos.r;

  if (states[r][c].state == 1 && states[r][c].last_state != states[r][c].state  && keys[i].active_key_position[0] == 0 ) {

    if (keys[i].type == SINGLE_ACTION_MODIFIER) {
      ADD_KEY_TO_PRESSED_REGISTER(i);
      PRINT_PRESSED_SINGLE_ACTION_KEY_REGISTER;
    }

    if (FN_LAYER_NOT_ACTIVE) {
      // send 1. layer
      SET_MODIFIER(keys[i].modifier_code[0]);
      set_keys(i, 0);
    } else {
      // send 3.layer
      SET_MODIFIER(keys[i].modifier_code[2]);
      set_keys(i, 2);
    }
  }
}

bool modifier_key_is_pressed() {
  //Returns false if no modifier keys are pressed, else returns true.
  for (int x = 0; x < 10; x++) {
    if (pressed_modifier_keys[x] != -1) {
      return true;
    }
  }
  return false;
}

void process_double_action_key(uint8_t i) {
  //Positions of the switches in the states array:
  uint8_t c1 = keys[i].first_switch_pos.c;
  uint8_t r1 = keys[i].first_switch_pos.r;
  uint8_t c2 = keys[i].second_switch_pos.c;
  uint8_t r2 = keys[i].second_switch_pos.r;

  //Enable modifier lock mode
  if (states[r1][c1].state == 1 && modifier_key_is_pressed()) {
    modifier_pressed_before_non_a_modifier_key = true;
    PRINT_PRESSED_SINGLE_ACTION_KEY_REGISTER;
  }

  if (FN_LAYER_NOT_ACTIVE) {
    //2. switch active
    if ( states[r2][c2].state == 1 && states[r2][c2].last_state != states[r2][c2].state ) {
      //send 2. layer
      SET_MODIFIER(keys[i].modifier_code[1]);
      set_keys(i, 1);
      keys[i].double_press = true;

      //1. switch pressed and then released
    } else if (states[r1][c1].state == 0 && keys[i].active_key_position[0] == 0 && states[r1][c1].last_state != states[r1][c1].state && !keys[i].double_press ) {
      //send 1. layer
      SET_MODIFIER(keys[i].modifier_code[0]);
      set_keys(i, 0);

      //The switch is already released so we need to release the 1. layer
      RELEASE_MODIFIER(keys[i].modifier_code[0]);
      release_key(i, 0);
      Keyboard.send_now();

      //Release all locked modifier keys:
      if (modifier_pressed_before_non_a_modifier_key) {
        for (int x = 0; x < 10; x++) {
          uint8_t index = pressed_modifier_keys[x];
          if (index != 0 && states[keys[index].first_switch_pos.r][keys[index].first_switch_pos.c].state == 0) {//the button has been released
            RELEASE_MODIFIER(keys[index].modifier_code[0]); // Release 1. layer
            release_key(index, 0);
            RELEASE_MODIFIER(keys[index].modifier_code[2]); // Release 3. layer
            release_key(index, 2);
            pressed_modifier_keys[x] = -1;
            modifier_pressed_before_non_a_modifier_key = false;
          }
        }
      }

      //1. switch pressed for a longer time than defined in DELAY_TIME
    } else if (states[r1][c1].state == 1 && keys[i].active_key_position[0] == 0 && millis() - states[r1][c1].switch_state_changed_time >= DELAY_TIME && !keys[i].double_press) {
      //send 1. layer
      SET_MODIFIER(keys[i].modifier_code[0]);
      set_keys(i, 0);
    }
  } else {
    //FN layer active
    if (states[r1][c1].state == 1 && states[r1][c1].last_state != states[r1][c1].state  && keys[i].active_key_position[0] == 0 ) {
      //send 3. layer
      SET_MODIFIER(keys[i].modifier_code[2]);
      set_keys(i, 2);
    }
  }
}

void process_double_action_key_no_delay(uint8_t i) {
  //Positions of the switches in the states array:
  uint8_t c1 = keys[i].first_switch_pos.c;
  uint8_t r1 = keys[i].first_switch_pos.r;
  uint8_t c2 = keys[i].second_switch_pos.c;
  uint8_t r2 = keys[i].second_switch_pos.r;

  //2. layer active:
  if ( states[r2][c2].state == 1 && states[r2][c2].last_state != states[r2][c2].state  ) {

    // Release first layer
    RELEASE_MODIFIER(keys[i].modifier_code[0]);
    release_key(i, 0);
    Keyboard.send_now();

    //send 2. layer
    SET_MODIFIER(keys[i].modifier_code[1]);
    set_keys(i, 1);
    keys[i].double_press = true;

    ADD_KEY_TO_PRESSED_REGISTER(i);
    PRINT_PRESSED_SINGLE_ACTION_KEY_REGISTER;

    //1. layer active -> no delay_time -> instant action
  } else if (states[r1][c1].state == 1 && states[r1][c1].last_state != states[r1][c1].state) {
    ADD_KEY_TO_PRESSED_REGISTER(i);
    PRINT_PRESSED_SINGLE_ACTION_KEY_REGISTER;

    //send 1. layer
    SET_MODIFIER(keys[i].modifier_code[0]);
    set_keys(i, 0);
  }
}

void set_keys(uint8_t i, uint8_t layer) {
  
  if (KEY_MEDIA_OR_KEY_SYSTEM(layer)) {
    //Multimedia keys work only when they are activated using the Keyboard.press() function.
    Keyboard.press(keys[i].key_code[layer]);
  } else {
    //Other keys are enabled using the Keyboard.set_keyX() functions

    //The for loop looks for a empty place in the active_key_register array.
    for (uint8_t index = 1; index < 7; index++) { //If already 6 keys are pressed nothing will happen.
      if (active_key_regiser[index] == 0 && keys[i].key_code[layer] != 0) {//Functions with only modifiers in them, will skip this part.

        keys[i].active_key_position[layer] = index;//Used for releasing the right keys later.
        active_key_regiser[index] = keys[i].key_code[layer];

        switch (index) {
          case 1:
            Keyboard.set_key1(keys[i].key_code[layer]);
            break;
          case 2:
            Keyboard.set_key2(keys[i].key_code[layer]);
            break;
          case 3:
            Keyboard.set_key3(keys[i].key_code[layer]);
            break;
          case 4:
            Keyboard.set_key4(keys[i].key_code[layer]);
            break;
          case 5:
            Keyboard.set_key5(keys[i].key_code[layer]);
            break;
          case 6:
            Keyboard.set_key6(keys[i].key_code[layer]);
            break;
        }
        break;
      }
    }
    Keyboard.send_now();
  }
}


bool pressed_modifier_keys_contain_key(uint8_t i) {
  for (int x = 0; x < 10; x++) {
    if (pressed_modifier_keys[x] == i) {
      return true;
    }
  }
  return false;
}

bool no_keys_pressed() {
  for (int c = 0; c < COLUMNS; c++) {
    for (int r = 0; r < ROWS; r++) {
      if (states[r][c].state == 1) {
        return false;
      }
    }
  }
  return true;
}

void reactivate_locked_modifiers() {
  for (int x = 0; x < 10; x++) {
    if (pressed_modifier_keys[x] != -1) {
      SET_MODIFIER(keys[pressed_modifier_keys[x]].modifier_code[0]);
    }
  }
}


void release_keys() {
  for (uint8_t i = 0; i < NUMBER_OF_KEYS; i++) {

    //if modifier lock is active for the current key -> skip the releasing process for this key:
    if (pressed_modifier_keys_contain_key(i) && modifier_pressed_before_non_a_modifier_key  && !no_keys_pressed()) {
      PRINT_PRESSED_SINGLE_ACTION_KEY_REGISTER;
      continue; //Take the next key in the for loop.
    }
    uint8_t c = keys[i].first_switch_pos.c;
    uint8_t r = keys[i].first_switch_pos.r;

    if (states[r][c].state == 0) { //reset press cycle, when the key is completely released.
      keys[i].double_press = false;
    }

    //Release locked modifier keys:
    if ( pressed_modifier_keys_contain_key(i) && no_keys_pressed()) {

      modifier_pressed_before_non_a_modifier_key = false;
      REMOVE_KEY_FROM_PRESSED_REGISTER(i);
      PRINT_PRESSED_SINGLE_ACTION_KEY_REGISTER;

      RELEASE_MODIFIER(keys[i].modifier_code[0]); // Release 1. layer modifier
      RELEASE_MODIFIER(keys[i].modifier_code[2]); // Release 3. layer modifier

      release_key(i, 0);//release 1. layer
      release_key(i, 2);//release 3. layer
      Keyboard.send_now();
    }

    //Release 1. and 3. layer
    if ((states[r][c].state == 0 && states[r][c].last_state != states[r][c].state) || FN_KEYS_ARE_RELEASED ) {
      if (KEY_MEDIA_OR_KEY_SYSTEM(0)) {
        Keyboard.release(keys[i].key_code[0]);
      }
      if (KEY_MEDIA_OR_KEY_SYSTEM(2)) {
        Keyboard.release(keys[i].key_code[2]);
      }

      RELEASE_MODIFIER(keys[i].modifier_code[0]); // Release 1. layer
      RELEASE_MODIFIER(keys[i].modifier_code[2]); // Release 3. layer

      REMOVE_KEY_FROM_PRESSED_REGISTER(i);
      PRINT_PRESSED_SINGLE_ACTION_KEY_REGISTER;

      //If a key is released on the 1. or on the FN layer (3. layer), resets it also the first and FN layer keys +  modifiers, but
      //it might be that a modifier that the 1. or the FN layer used was locked before activating the FN layer on a another key,
      //therefore we need to check if there were locked modifiers and make sure they stay locked.
      reactivate_locked_modifiers();

      release_key(i, 0);//1. layer
      release_key(i, 2);//3. layer
      Keyboard.send_now();

      last_action_time = millis();
    }

    //Release 2. layer
    if (keys[i].type == DOUBLE_ACTION || keys[i].type == DOUBLE_ACTION_NO_DELAY) {

      c = keys[i].second_switch_pos.c;
      r = keys[i].second_switch_pos.r;

      if (states[r][c].state == 0 && states[r][c].last_state != states[r][c].state) { //2. layer released
        if (KEY_MEDIA_OR_KEY_SYSTEM(1)) {
          Keyboard.release(keys[i].key_code[1]);
        }
        RELEASE_MODIFIER(keys[i].modifier_code[1]); // Release 2. layer modifier
        release_key(i, 1);// Release 2. layer
        Keyboard.send_now();

        last_action_time = millis();
      }
    }
  }
}

void release_key(uint8_t i, uint8_t layer) {
  uint8_t index = keys[i].active_key_position[layer];
  if (index != 0) {
    keys[i].active_key_position[layer] = 0;
    active_key_regiser[index] = 0;

    switch (index) {
      case 1:
        Keyboard.set_key1(0);
        break;
      case 2:
        Keyboard.set_key2(0);
        break;
      case 3:
        Keyboard.set_key3(0);
        break;
      case 4:
        Keyboard.set_key4(0);
        break;
      case 5:
        Keyboard.set_key5(0);
        break;
      case 6:
        Keyboard.set_key6(0);
        break;
    }
  }
}

void update_last_state() {
  //updates the last_state variables of the state array
  for (int c = 0; c < COLUMNS; c++) {
    for (int r = 0; r < ROWS; r++) {
      states[r][c].last_state = states[r][c].state;
    }
  }
}

void set_fn_lock() {
  //both FN keys pressed at the same time
  if (FN_KEYS_ARE_PUSHED) {
    fn_lock_is_on = !fn_lock_is_on;
    if (fn_lock_is_on) {
      digitalWrite(LED2, HIGH);
    } else {
      digitalWrite(LED2, LOW);
    }
  }
}

void set_leds() {
  // Checks the caps lock bit:
  if (keyboard_leds & (1 << USB_LED_CAPS_LOCK)) {
    digitalWrite(LED1, HIGH);
  } else {
    digitalWrite(LED1, LOW);
  }
}

void set_sleep_mode() {
  //The controller goes to 'sleep mode' after time defined in DELAY_SLEEP_MODE has passed without any interrupts.
  if (millis() - last_action_time >= DELAY_SLEEP_MODE) {
    delay(SLEEP_DELAY_TIME);
  }
}

