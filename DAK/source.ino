/*
    DAK - is a firmware for Double Action Keyboards
    source.ino - includes all functions used in the main loop.

    Copyright (C) 2022  Jaakob Lidauer

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

#ifndef USE_COLUMN_MUX
    // Set one column active (HIGH)
    digitalWrite(COLUMN_PINS[c], HIGH);
#else
    // set correct bits active to column mux
    for (int mux_bit = 0; mux_bit < MUX_COLUMN_BITS; mux_bit++) {
      digitalWrite(MUX_COLUMN_PINS[mux_bit], (COLUMN_PINS[c] >> mux_bit) & 0b1);
    }
    digitalWrite(MUX_COLUMN_INPUT_PIN, 1);
    //delay(1);
#endif
    uint32_t millis_tmp;

    for (int r = 0; r < ROWS; r++) {
      
      uint8_t pin_state = digitalRead(ROW_PINS[r]);
      //Serial.println(analogRead(ROW_PINS[r]));

      if (states[r][c].switch_bounce_time != 0 && time_current - states[r][c].switch_bounce_time >= DELAY_TIME_BOUNCE) { 
        // If the switch is in a constant state -> add the change to the states array.
        
        millis_tmp = millis();
        last_action_time = millis_tmp;

        states[r][c].state = pin_state;
        states[r][c].switch_bounce_time = 0;
        states[r][c].switch_state_changed_time = millis_tmp;
      }
      
      //Set time:
      if (pin_state != states[r][c].state && states[r][c].switch_bounce_time == 0) {
        // State of the switch has changed for the first time.
        states[r][c].switch_bounce_time = time_current;

      } else if (pin_state == states[r][c].state && states[r][c].switch_bounce_time != 0) {
        // The state of the switch is not definite -> reset bounce timer
        states[r][c].switch_bounce_time = 0;
      }
    }

#ifndef USE_COLUMN_MUX
    digitalWrite(COLUMN_PINS[c], LOW);
#else
    digitalWrite(MUX_COLUMN_INPUT_PIN, 0);
#endif

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

// Updated key state by putting the key to ENABLED if the 
// key has been released and it was in DISABLED state.
void update_key_state() {
  for (uint8_t i = 0; i < NUMBER_OF_KEYS; i++) {

    if (keys[i].state == ENABLED){
      continue; // Skip key if it is already enabled.
    }

    uint8_t c1 = keys_const[i].first_switch_pos.c;
    uint8_t r1 = keys_const[i].first_switch_pos.r;
    uint8_t c2 = keys_const[i].second_switch_pos.c;
    uint8_t r2 = keys_const[i].second_switch_pos.r;

    if (states[r1][c1].state == 0 && states[r2][c2].state == 0 ){
      keys[i].state = ENABLED;
    }

  }
}

void send_keys() {
  
  for (uint8_t i = 0; i < NUMBER_OF_KEYS; i++) {

    if (keys[i].state == DISABLED){
      continue; // skip key if it is not in use
    }

    KeyType type = keys_const[i].type2; // FN-layer

    if (keyboard_layer == L1){
      type = keys_const[i].type;
    }
    
    if (type == ADDITIVE_ACTION) {
      process_additive_action_key(i);
    } else if (type == DOUBLE_ACTION) {
      process_double_action_key(i);
    } else if (type == TOGGLE_ACTION) {
      process_double_action_key_no_delay(i);
    }
  }
}

void process_additive_action_key(uint8_t i) { // process normal key

  uint8_t c1 = keys_const[i].first_switch_pos.c;
  uint8_t r1 = keys_const[i].first_switch_pos.r;
  uint8_t c2 = keys_const[i].second_switch_pos.c;
  uint8_t r2 = keys_const[i].second_switch_pos.r;

  // First action
  if (states[r1][c1].state == 1 && states[r1][c1].last_state != states[r1][c1].state  && 
    keys[i].active_key_position[0 + keyboard_layer] == 0 ) {

    if (keys[i].config_layer[0 + keyboard_layer] == MODIFIER) {
      ADD_KEY_TO_PRESSED_MODIFIER_KEYS_REGISTER(i);
      PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;
    }
   
    // send 1. action
    SET_MODIFIER(keys_const[i].modifier_code[0 + keyboard_layer]);
    set_keys(i, 0 + keyboard_layer);
  }

  // Second action
  if (states[r2][c2].state == 1 && states[r2][c2].last_state != states[r2][c2].state  && 
    keys[i].active_key_position[1 + keyboard_layer] == 0 ) {

    if (keys[i].config_layer[1 + keyboard_layer] == MODIFIER) {
      ADD_KEY_TO_PRESSED_MODIFIER_KEYS_REGISTER(i + NUMBER_OF_KEYS);
      PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;
    }

    // send 2. action
    SET_MODIFIER(keys_const[i].modifier_code[1 + keyboard_layer]);
    set_keys(i, 1 + keyboard_layer);
  }
}

bool modifier_key_is_pressed() {
  // Returns false if no modifier keys are pressed, else returns true.
  for (int x = 0; x < 10; x++) {
    if (pressed_modifier_keys[x] != -1) {
      return true;
    }
  }
  return false;
}

void process_double_action_key(uint8_t i) {

  // Positions of the switches in the states array:
  uint8_t c1 = keys_const[i].first_switch_pos.c;
  uint8_t r1 = keys_const[i].first_switch_pos.r;
  uint8_t c2 = keys_const[i].second_switch_pos.c;
  uint8_t r2 = keys_const[i].second_switch_pos.r;

  // Enable modifier lock mode
  if (states[r1][c1].state == 1 && modifier_key_is_pressed()) {
    modifier_pressed_before_non_a_modifier_key = true;
    PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;
  }

  // 2. action active
  if ( states[r2][c2].state == 1 && states[r2][c2].last_state != states[r2][c2].state ) {
    
    // Release 1. layer keys, should not be neccessary in this case, TODO.
    //RELEASE_MODIFIER(keys_const[i].modifier_code[0]);
    //release_key(i, 0);
    //reactivate_locked_modifiers(i);
    //Keyboard.send_now();
    
    // Send 2. action
    SET_MODIFIER(keys_const[i].modifier_code[1 + keyboard_layer]);
    set_keys(i, 1 + keyboard_layer);
    keys[i].double_press = true;

    if (keys[i].config_layer[1 + keyboard_layer] == MODIFIER) {
      ADD_KEY_TO_PRESSED_MODIFIER_KEYS_REGISTER(i + NUMBER_OF_KEYS);
      PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;
    }

    // 1. action pressed and then released
  } else if (states[r1][c1].state == 0 && keys[i].active_key_position[0 + keyboard_layer] == 0 && 
    states[r1][c1].last_state != states[r1][c1].state && !keys[i].double_press ) {
    
    // Send 1. action
    SET_MODIFIER(keys_const[i].modifier_code[0 + keyboard_layer]);
    set_keys(i, 0 + keyboard_layer);

    // The switch is already released so we need to release the 1. action
    RELEASE_MODIFIER(keys_const[i].modifier_code[0 + keyboard_layer]);
    release_key(i, 0 + keyboard_layer);
    Keyboard.send_now();
    
    // Release all locked modifier keys:
    if (modifier_pressed_before_non_a_modifier_key) {
      for (int x = 0; x < 10; x++) {
        int16_t index = pressed_modifier_keys[x];
        if (index != -1) {

          if ( states[keys_const[index].first_switch_pos.r][keys_const[index].first_switch_pos.c].state == 0) { // the button has been released
            
            RELEASE_MODIFIER(keys_const[index].modifier_code[0 + keyboard_layer]); // Release 1. action
            release_key(index, 0);
            RELEASE_MODIFIER(keys_const[index].modifier_code[1 + keyboard_layer]); // Release 2. action
            release_key(index, 1);
            pressed_modifier_keys[x] = -1;
            modifier_pressed_before_non_a_modifier_key = false;

          }
        }
      }
    }

    // 1. switch pressed for a longer time than defined in DELAY_TIME
  } else if (states[r1][c1].state == 1 && keys[i].active_key_position[0 + keyboard_layer] == 0 && 
    millis() - states[r1][c1].switch_state_changed_time >= DELAY_TIME && !keys[i].double_press) {
    
    // Send 1. action
    SET_MODIFIER(keys_const[i].modifier_code[0 + keyboard_layer]);
    set_keys(i, 0 + keyboard_layer);

    if (keys[i].config_layer[0 + keyboard_layer] == MODIFIER) {
      ADD_KEY_TO_PRESSED_MODIFIER_KEYS_REGISTER(i);
      PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;
    }
  
  }
}

void process_double_action_key_no_delay(uint8_t i) {

  // Positions of the switches in the states array:
  uint8_t c1 = keys_const[i].first_switch_pos.c;
  uint8_t r1 = keys_const[i].first_switch_pos.r;
  uint8_t c2 = keys_const[i].second_switch_pos.c;
  uint8_t r2 = keys_const[i].second_switch_pos.r;
  
  // 2. action active:
  if (states[r2][c2].state == 1 && states[r2][c2].last_state != states[r2][c2].state  ) {

    // Release first action
    RELEASE_MODIFIER(keys_const[i].modifier_code[0 + keyboard_layer]);
    release_key(i, 0 + keyboard_layer);
    reactivate_locked_modifiers(i);
    Keyboard.send_now();

    // Send 2. action
    SET_MODIFIER(keys_const[i].modifier_code[1 + keyboard_layer]);
    set_keys(i, 1 + keyboard_layer);
    keys[i].double_press = true;

    if (keys[i].config_layer[1 + keyboard_layer] == MODIFIER) {
      ADD_KEY_TO_PRESSED_MODIFIER_KEYS_REGISTER(i + NUMBER_OF_KEYS);
      PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;
    }

    // 1. action active -> no delay_time -> instant action
  } else if (states[r1][c1].state == 1 && states[r1][c1].last_state != states[r1][c1].state/* && states[r2][c2].state == 0*/) {

//      // Release second layer
//      RELEASE_MODIFIER(keys[i].modifier_code[1]);
//      release_key(i, 1);
//      reactivate_locked_modifiers(-1);
//      Keyboard.send_now();

    if (keys[i].config_layer[0 + keyboard_layer] == MODIFIER) {
      ADD_KEY_TO_PRESSED_MODIFIER_KEYS_REGISTER(i);
      PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;
    }

    // Send 1. layer
    SET_MODIFIER(keys_const[i].modifier_code[0 + keyboard_layer]);
    set_keys(i, 0 + keyboard_layer);
  }
}

void set_keys(uint8_t i, uint8_t layer) {

  if (KEY_MEDIA_OR_KEY_SYSTEM(layer)) {
    
    // Multimedia keys work only when they are activated using the Keyboard.press() function.
    Keyboard.press(keys_const[i].key_code[layer]);
    
#ifdef DEBUG_PRINT
    Serial.print("Media key pressed: ");
    Serial.println(keys_const[i].key_code[layer]);
#endif
    
  } else {
    // Other keys are enabled using the Keyboard.set_keyX() functions

    // The for loop looks for a empty place in the active_key_register array.
    for (uint8_t index = 1; index < 7; index++) { // If already 6 keys are pressed nothing will happen.
      
      if (active_key_regiser[index] == 0 && keys_const[i].key_code[layer] != 0) { // Functions with only modifiers in them, will skip this part.

        keys[i].active_key_position[layer] = index; // Used for releasing the right keys later.
        active_key_regiser[index] = keys_const[i].key_code[layer]; // Used keeping track of what Keyboard.set_keyX() are currently in use.

        switch (index) {
          case 1:
            Keyboard.set_key1(keys_const[i].key_code[layer]);
            break;
          case 2:
            Keyboard.set_key2(keys_const[i].key_code[layer]);
            break;
          case 3:
            Keyboard.set_key3(keys_const[i].key_code[layer]);
            break;
          case 4:
            Keyboard.set_key4(keys_const[i].key_code[layer]);
            break;
          case 5:
            Keyboard.set_key5(keys_const[i].key_code[layer]);
            break;
          case 6:
            Keyboard.set_key6(keys_const[i].key_code[layer]);
            break;
        }
        break;
      }
    }
    Keyboard.send_now();
  }
}

bool pressed_modifier_keys_contains_key(uint8_t i) {
  for (int x = 0; x < 10; x++) {
    if (pressed_modifier_keys[x] == i || pressed_modifier_keys[x] == i + NUMBER_OF_KEYS) {
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

// Returns true if all keys are released and their last state is also released (==0).
bool no_keys_pressed_and_in_steady_state() {
  for (int c = 0; c < COLUMNS; c++) {
    for (int r = 0; r < ROWS; r++) {
      if (states[r][c].state == 1 || states[r][c].last_state == 1) {
        return false;
      }
    }
  }
  return true;
}

void reactivate_locked_modifiers(int skip_this_index) {
  // Set skip_this_index to -1 if not used

  for (int x = 0; x < 10; x++) {
    
    int index = pressed_modifier_keys[x];
    
    if (index != -1 && index != skip_this_index) {
      
      if (index < NUMBER_OF_KEYS) {
        // First layer
        SET_MODIFIER(keys_const[index].modifier_code[0 + keyboard_layer]);
      } else {
        // Second layer modifier activation
        SET_MODIFIER(keys_const[index - NUMBER_OF_KEYS].modifier_code[1 + keyboard_layer]);
      }
    }
  }
}

// Function for releasing the keys
void release_keys() {

  bool no_keys_pressed_now = no_keys_pressed();

  for (uint8_t i = 0; i < NUMBER_OF_KEYS; i++) { // Loop over all keys

    // If modifier lock is active for the current key -> skip the releasing process for this key:
    if (pressed_modifier_keys_contains_key(i) && modifier_pressed_before_non_a_modifier_key  && !no_keys_pressed_now) {
      PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;
      continue; // Take the next key in the for loop.
    }
    uint8_t c = keys_const[i].first_switch_pos.c;
    uint8_t r = keys_const[i].first_switch_pos.r;

    if (states[r][c].state == 0) { // Reset press cycle, when the key is completely released.
      keys[i].double_press = false;
    }

    // Release locked modifier keys:
    if ( pressed_modifier_keys_contains_key(i) && no_keys_pressed_now) {
      
      // Reset flag
      modifier_pressed_before_non_a_modifier_key = false;

      REMOVE_KEY_FROM_PRESSED_MODIFIER_KEYS_REGISTER(i);
      REMOVE_KEY_FROM_PRESSED_MODIFIER_KEYS_REGISTER(i + NUMBER_OF_KEYS);

      // Debugging
      PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;

      RELEASE_MODIFIER(keys_const[i].modifier_code[0 + keyboard_layer]); // Release 1. action modifier
      RELEASE_MODIFIER(keys_const[i].modifier_code[1 + keyboard_layer]); // Release 2. action modifier

      release_key(i, 0 + keyboard_layer); // Release 1. action
      release_key(i, 1 + keyboard_layer); // Release 2. action

      Keyboard.send_now();
    }

    // Release 1. action
    if ((states[r][c].state == 0 && states[r][c].last_state != states[r][c].state) /*|| FN_KEYS_ARE_RELEASED -duplicate*/ ) {

      if (KEY_MEDIA_OR_KEY_SYSTEM(0 + keyboard_layer)) {
        Keyboard.release(keys_const[i].key_code[0 + keyboard_layer]);
#ifdef DEBUG_PRINT
    Serial.print("Media key released: ");
    Serial.println(keys_const[i].key_code[0 + keyboard_layer]);
#endif
      }

      RELEASE_MODIFIER(keys_const[i].modifier_code[0 + keyboard_layer]); // Release 1. layer

      REMOVE_KEY_FROM_PRESSED_MODIFIER_KEYS_REGISTER(i); // should not happen
      PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;

      // If a key is released on the 1. or on the FN layer (3. action), it resets also the first and FN layer keys +  modifiers, but
      // it might be that a modifier that the 1. or the FN layer used was locked before activating the FN layer on a another key,
      // therefore we need to check if there were locked modifiers and make sure they stay locked.
      reactivate_locked_modifiers(-1);

      release_key(i, 0 + keyboard_layer); // 1. action
      Keyboard.send_now();

      //last_action_time = millis();
    }

    // Release 2. action
    c = keys_const[i].second_switch_pos.c;
    r = keys_const[i].second_switch_pos.r;

    if (states[r][c].state == 0 && states[r][c].last_state != states[r][c].state) { //2. action released
      if (KEY_MEDIA_OR_KEY_SYSTEM(1 + keyboard_layer)) {
        Keyboard.release(keys_const[i].key_code[1 + keyboard_layer]);
#ifdef DEBUG_PRINT
    Serial.print("Media key released: ");
    Serial.println(keys_const[i].key_code[1 + keyboard_layer]);
#endif
      }
      RELEASE_MODIFIER(keys_const[i].modifier_code[1 + keyboard_layer]); // Release 2. action modifier
      release_key(i, 1 + keyboard_layer);// Release 2. action
      Keyboard.send_now();

      REMOVE_KEY_FROM_PRESSED_MODIFIER_KEYS_REGISTER(i + NUMBER_OF_KEYS); // Should not happen
      PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;

      //last_action_time = millis();
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
  // Updates the last_state variables of the state array

  for (int c = 0; c < COLUMNS; c++) {
    for (int r = 0; r < ROWS; r++) {
      states[r][c].last_state = states[r][c].state;
    }
  }
}

void set_fn_lock() {
  // Lock or release FN layer if both FN keys pressed at the same time.

  if (FN_KEYS_ARE_PUSHED) {
    fn_lock_is_on = !fn_lock_is_on;
    if (fn_lock_is_on) {
      digitalWrite(LED2, HIGH);
    } else {
      digitalWrite(LED2, LOW);
    }
  }
}

void reset_keyboard(){
  // This function is used to reset the keyboard when the layer is changed.

  // Reset flag
  modifier_pressed_before_non_a_modifier_key = false;

  // Release all keys
  for (uint8_t i = 0; i < NUMBER_OF_KEYS; i++) { // Loop over all keys

    uint8_t c1 = keys_const[i].first_switch_pos.c;
    uint8_t r1 = keys_const[i].first_switch_pos.r;
    uint8_t c2 = keys_const[i].second_switch_pos.c;
    uint8_t r2 = keys_const[i].second_switch_pos.r;

    if (states[r1][c1].state == 1 || states[r2][c2].state == 1 ){
      // Disable key if it is pressed during the layer change.
      // This is done to avoid unwanted keystrokes on layer changes and
      // ensure that the keyboard works even if one of the keys would get stuck.
      keys[i].state = DISABLED;
    }

    keys[i].double_press = false;
  
    REMOVE_KEY_FROM_PRESSED_MODIFIER_KEYS_REGISTER(i);
    REMOVE_KEY_FROM_PRESSED_MODIFIER_KEYS_REGISTER(i + NUMBER_OF_KEYS);

    // Debugging
    PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER;

    RELEASE_MODIFIER(keys_const[i].modifier_code[0 + keyboard_layer]); // Release 1. action modifier
    RELEASE_MODIFIER(keys_const[i].modifier_code[1 + keyboard_layer]); // Release 2. action modifier

    release_key(i, 0 + keyboard_layer); // Release 1. action
    release_key(i, 1 + keyboard_layer); // Release 2. action
 
    Keyboard.send_now();
  
    // Special handling of media/system keys
    if (KEY_MEDIA_OR_KEY_SYSTEM(0 + keyboard_layer)) {
 //     Keyboard.release(keys_const[i].key_code[0 + keyboard_layer]);
#ifdef DEBUG_PRINT
//    Serial.print("Media key released: ");
 //   Serial.println(keys_const[i].key_code[0 + keyboard_layer]);
#endif
    }
    if (KEY_MEDIA_OR_KEY_SYSTEM(1 + keyboard_layer)) {
  //    Keyboard.release(keys_const[i].key_code[1 + keyboard_layer]);
#ifdef DEBUG_PRINT
  //  Serial.print("Media key released: ");
  //  Serial.println(keys_const[i].key_code[1 + keyboard_layer]);
#endif
    }

  }
  Keyboard.releaseAll();
  //last_action_time = millis();
}

void set_current_layer(){

  if (keyboard_layer == L1 && !FN_LAYER_NOT_ACTIVE){
    // FN layer has been activated -> change layer to L2
    reset_keyboard();
    keyboard_layer = L2;
#ifdef DEBUG_PRINT
    Serial.print("Layer ");
    Serial.println(keyboard_layer);
#endif

  } else if (keyboard_layer == L2 && FN_LAYER_NOT_ACTIVE){
    // FN layer has been released -> change to L1
    reset_keyboard();
    keyboard_layer = L1;
#ifdef DEBUG_PRINT
    Serial.print("Layer ");
    Serial.println(keyboard_layer);
#endif

  } else {
    // No change in layer
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
  // The controller goes to 'sleep mode' after time defined in DELAY_SLEEP_MODE has passed without any interrupts.
  if (millis() - last_action_time >= DELAY_SLEEP_MODE) {
    delay(SLEEP_DELAY_TIME);
  }
}