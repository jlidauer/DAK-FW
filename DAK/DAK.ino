/*
    DAK - is a firmware for Double Action Keyboards
    Version: 1.1

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

#include "hw_config.h"
#include "constants.h"
#include "layout_config_FI.h"

// Implementations of all other functions can be found in the source.ino file.

// Keeps track of all modifier keys that have been pressed before a normal key.
// Stores their index in the keys array.
int32_t pressed_modifier_keys[10] = { -1};

// Used to enter modifier locking mode
bool modifier_pressed_before_non_a_modifier_key = false;

//Keeps the states of all switches
struct State states[ROWS][COLUMNS] = {0};

// First byte is for storing active modifier keys.
// Other bytes store all currently pressed keys -> max 6 keys can be pressed simultaneously.
// Value of the byte is equal to the key code of the pressed key.
uint8_t active_key_regiser[7] = {0x00};

// To keep track of the state of FN-lock
bool fn_lock_is_on = false;

// Stores the time when the last key was released, used for entering sleep mode.
unsigned long last_action_time = 0;

// State of the keyboard (i.e. current layer).
CurrentLayer keyboard_layer = L1;

void setup() {
  // For debugging:
#if defined DEBUG_PRINT_STATES_ARRAY || defined DEBUG_PRINT
  Serial.begin(9600);
#endif

  // Initialize array
  for (int x = 0; x < 10; x++) {
    pressed_modifier_keys[x] = -1;
  }

  //Set IO pins
  for (int r = 0; r < ROWS; r++) {
    pinMode(ROW_PINS[r], INPUT);
  }

#ifndef USE_COLUMN_MUX
  for (int c = 0; c < COLUMNS; c++) {
    pinMode(COLUMN_PINS[c], OUTPUT);
  }
#else
  pinMode(MUX_COLUMN_INPUT_PIN, OUTPUT);

  for (int m_c = 0; m_c < MUX_COLUMN_BITS; m_c++) {
    pinMode(MUX_COLUMN_PINS[m_c], OUTPUT);
  }
#endif

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  initialize_keys_list();
}

void initialize_keys_list() {
  // Initialize keyconfigs for 1. and 2. layers. E.g. determine if it is a modifier or not.
  // Key actions that have only modifiers are MODIFIER keys that are locked down to allow easy
  // actiovation of keyboard shortcuts or combinations
  
  for (uint8_t i = 0; i < NUMBER_OF_KEYS; i++) {
    // Loop over layers
    for(uint8_t layer = 0; layer < 4; layer++){
      if(keys_const[i].key_code[layer] == 0 && keys_const[i].modifier_code[layer] != 0){
        keys[i].config_layer[layer] = MODIFIER;
      }else{
        keys[i].config_layer[layer] = NORMAL;
      }
    }
  }
}

void loop() {
  //unsigned long t = micros();

  read_switches();
  
  set_fn_lock();
  set_current_layer();
  send_keys();
  release_keys();
  
  update_key_state();
  update_last_state();
  set_leds();
  set_sleep_mode();

#ifdef DEBUG_PRINT
  // Debugging of active_key_regiser
  static uint8_t active_key_regiser_last[7] = {0x00};

  if (memcmp(active_key_regiser,active_key_regiser_last,7) != 0){
    // Print if register has changed

    for(int i = 0; i < 8; i++){
      Serial.print(0x1 & (active_key_regiser[0]>>i));
    }
    Serial.print("\t");

    for(int i = 1; i<7; i++){
      Serial.print(active_key_regiser[i]);
      Serial.print("\t");
    }
    
    Serial.println("");
  }
  
  // Copy for next round
  memcpy(active_key_regiser_last,active_key_regiser,7);
#endif

  //Serial.println(micros() - t);
  //delay(50);

  // Teensy 3.2:
  // Total time per loop: 347 us @ 96 MHz -> 2.9 kHz
  //                      650 us @ 48 MHz -> 1.5 kHz
  // In sleep mode -> 0.1 kHz
}