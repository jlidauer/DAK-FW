/*
    DAK - is a firmware for Double Action Keyboards
    Version: 0.9

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

#include "key_matrix.h"
#include "constants.h"
#include "layout_FI.h"
//All other functions can be found in the source.ino file.

//Keeps track of all modifier keys that have been pressed before a normal key.
//Stores their index in the keys array.
int8_t pressed_modifier_keys[10] = { -1};

//Used to enter modifier locking mode
bool modifier_pressed_before_non_a_modifier_key = false;

//Keeps the states of all switches
struct State states[ROWS][COLUMNS] = {0};

//First byte is for storing active modifier keys.
//Other bytes store all currently pressed keys -> max 6 keys can be pressed simultaneously.
//Value of the byte is equal to the key code of the pressed key.
uint8_t active_key_regiser[7] = {0x00};

//To keep track of the state of FN-lock
bool fn_lock_is_on = false;

//Stores the time when the last key was released, used for entering sleep mode.
unsigned long last_action_time = 0;

//Triggered when FN-key is released.
bool wait_untill_all_keys_are_released = false;

void setup() {
  //For debugging:
#ifdef DEBUG_PRINT_STATES_ARRAY
  Serial.begin(9600);
#endif

  //Initialize array
  for (int x = 0; x < 10; x++) {
    pressed_modifier_keys[x] = -1;
  }

  //Set IO pins
  for (int r = 0; r < ROWS; r++) {
    pinMode(ROW_PINS[r], INPUT);
  }
  for (int c = 0; c < COLUMNS; c++) {
    pinMode(COLUMN_PINS[c], OUTPUT);
  }
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

}

void loop() {
  //unsigned long t = micros();

  read_switches();
  if (!wait_untill_all_keys_are_released) {//Eliminates unwanted key strokes when FN-layer is released.
    set_fn_lock();
    send_keys();
    release_keys();
  }
  update_last_state();
  set_leds();
  set_sleep_mode();

  //Serial.println(micros() - t);
  //delay(50);

  //Teensy 3.2:
  //Total time per loop: 347 us @ 96 MHz -> 2.9 kHz
  //                     650 us @ 48 MHz -> 1.5 kHz
  //In sleep mode -> 0.1 kHz
}
