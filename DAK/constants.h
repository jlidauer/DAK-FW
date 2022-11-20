/*
    DAK - is a firmware for Double Action Keyboards
    constants.h - contains constants, macros and structs that are used in the program

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

#ifndef CONSTANTS
#define CONSTANTS

#define DELAY_TIME          400     //ms      Defines how long the first layer needs to be pressed before the keystroke is sent.
#define DELAY_TIME_BOUNCE   60      //*0.1 ms Used to avoid double clicks. If double clicks occur increase this value.
#define DELAY_SLEEP_MODE    10000   //ms      Time after the keyboard goes to sleep mode.
#define SLEEP_DELAY_TIME    10      //ms      Delay that is added in sleep mode to each loop. To disable the sleep mode, set this value to zero.

// Used for setting FN lock and testing if FN layer is active.
#define FN1_ROW FN1[1]
#define FN1_COL FN1[0]
#define FN2_ROW FN2[1]
#define FN2_COL FN2[0]
#define FN_LAYER_NOT_ACTIVE     ((states[FN1_ROW][FN1_COL].state == 0 && states[FN2_ROW][FN2_COL].state == 0) && !fn_lock_is_on)== true && (states[FN2_ROW][FN2_COL].last_state == states[FN2_ROW][FN2_COL].state && states[FN1_ROW][FN1_COL].state == states[FN1_ROW][FN1_COL].last_state)==true
#define FN_KEYS_ARE_RELEASED    (states[FN1_ROW][FN1_COL].state == 0 && states[FN2_ROW][FN2_COL].state == 0 && (states[FN2_ROW][FN2_COL].last_state != states[FN2_ROW][FN2_COL].state || states[FN1_ROW][FN1_COL].state != states[FN1_ROW][FN1_COL].last_state))
#define FN_KEYS_ARE_PUSHED      (states[FN1_ROW][FN1_COL].state == 1 && states[FN2_ROW][FN2_COL].state == 1 && (states[FN2_ROW][FN2_COL].last_state != states[FN2_ROW][FN2_COL].state || states[FN1_ROW][FN1_COL].state != states[FN1_ROW][FN1_COL].last_state))

// Checks if the key code of a key is a media key or a system key
#define KEY_MEDIA_OR_KEY_SYSTEM(layer) ((keys_const[i].key_code[layer] & 0xFF00) == 0xE400 ||(keys_const[i].key_code[layer] & 0xFF00) == 0xE200)

#define SET_MODIFIER(mod)      active_key_regiser[0] |=  mod; Keyboard.set_modifier(active_key_regiser[0]);
#define RELEASE_MODIFIER(mod)  active_key_regiser[0] &= ~mod; Keyboard.set_modifier(active_key_regiser[0]);

// LED codes, used to turn the LEDs on/off
#define USB_LED_NUM_LOCK 0
#define USB_LED_CAPS_LOCK 1
#define USB_LED_SCROLL_LOCK 2
#define USB_LED_COMPOSE 3
#define USB_LED_KANA 4

// Functions to lock modifiers:
#define ADD_KEY_TO_PRESSED_MODIFIER_KEYS_REGISTER(i) \
  for(int x = 0;x<10;x++){\
    if(pressed_modifier_keys[x]==-1){\
      pressed_modifier_keys[x]=i;break;\
    }\
  }

#define REMOVE_KEY_FROM_PRESSED_MODIFIER_KEYS_REGISTER(i) \
  for(int x = 0;x<10;x++){\
    if(pressed_modifier_keys[x] == i){\
      pressed_modifier_keys[x]=-1;break;\
    }\
  }

// For debugging
#define PRINT_PRESSED_ADDITIVE_ACTION_KEY_REGISTER /* \
  for(int x = 0;x<10;x++){ \
    Serial.print(pressed_modifier_keys[x]); \
    Serial.print('\t'); \
  }Serial.print('\n'); */

// enum for storing the active layer
typedef enum current_layer {
  L1 = 0,
  L2 = 2
} CurrentLayer;

// enum for describing the state of a key, all pressed keys are disable on layer change and activated once they are released.
typedef enum key_state {
  DISABLED,
  ENABLED
} KeyState;


// Key types used to define the behavior a key.
typedef enum key_type {
  ADDITIVE_ACTION,
  DOUBLE_ACTION,
  TOGGLE_ACTION,
} __attribute__((packed)) KeyType;

typedef enum key_configuration {
  MODIFIER,
  NORMAL,
}__attribute__((packed)) KeyConfig;

// Used to store the position of a switch in the struct KeyConst.
struct Rc {
  uint8_t c; // column
  uint8_t r; // row
}__attribute__((packed));

// Stores all not constant information of one key.
struct Key {

  // Used to keep track of the current status of the key.
  bool double_press;

  // Stores the place of the pressed key in the active_key_register, each layer has one cell.
  uint8_t active_key_position[4];

  KeyConfig config_layer[4]; // config of each layer (is it a modifier or not)
  
  KeyState state; // Used for disabling or enabling a key

}__attribute__((packed));

// Stores all constant information of one key.
struct KeyConst {
  
  KeyType type;  // Key type of normal-layer
  KeyType type2; // Key type of FN-layer

  // Key codes for all four actions of the two double actions layers (normal-layer + FN-layer).
  uint16_t key_code[4];      // Order: {1. normal-layer, 2. normal-layer, 1. FN-layer, 2. FN-layer}
  uint16_t modifier_code[4]; // Order: {1. normal-layer, 2. normal-layer, 1. FN-layer, 2. FN-layer}

  // Defines the index of the switch in the states array
  struct Rc first_switch_pos;
  struct Rc second_switch_pos;

}__attribute__((packed));

// Stores the state of one switch in the states array.
struct State {
  
  uint8_t state; // 1 or 0
  uint8_t last_state; // 1 or 0

  // Time when the state changed for the last time.
  uint32_t switch_state_changed_time;

  // Used to filter bouncing.
  uint32_t switch_bounce_time;

}__attribute__((packed));

#endif
