/*
    DAK - is a firmware for Double Action Keyboards
    constants.h - contains constants, macros and structures that are used in the program

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

#ifndef CONSTANTS
#define CONSTANTS

#define DELAY_TIME          400     //ms      Defines how long the first layer needs to be pressed before the keystroke is sent.
#define DELAY_TIME_BOUNCE   60      //*0.1 ms Used to avoid double clicks. If double clicks occur increase this value.
#define DELAY_SLEEP_MODE    10000   //ms      Time after the keyboard goes to sleep mode.
#define SLEEP_DELAY_TIME    10      //ms      Delay that is added in sleep mode to each loop. To disable the sleep mode, set this value to zero.

//Used for setting FN lock and testing if FN layer is active.
#define FN_LAYER_NOT_ACTIVE     ((states[FN1_ROW][FN1_COL].state == 0 && states[FN2_ROW][FN2_COL].state == 0) && !fn_lock_is_on)== true && (states[FN2_ROW][FN2_COL].last_state == states[FN2_ROW][FN2_COL].state && states[FN1_ROW][FN1_COL].state == states[FN1_ROW][FN1_COL].last_state)==true
#define FN_KEYS_ARE_RELEASED    (states[FN1_ROW][FN1_COL].state == 0 && states[FN2_ROW][FN2_COL].state == 0 && (states[FN2_ROW][FN2_COL].last_state != states[FN2_ROW][FN2_COL].state || states[FN1_ROW][FN1_COL].state != states[FN1_ROW][FN1_COL].last_state))
#define FN_KEYS_ARE_PUSHED      (states[FN1_ROW][FN1_COL].state == 1 && states[FN2_ROW][FN2_COL].state == 1 && (states[FN2_ROW][FN2_COL].last_state != states[FN2_ROW][FN2_COL].state || states[FN1_ROW][FN1_COL].state != states[FN1_ROW][FN1_COL].last_state))

//Checks if the key code of a key is a media key or a system key
#define KEY_MEDIA_OR_KEY_SYSTEM(layer) ((keys[i].key_code[layer] & 0xFF00) == 0xE400 ||(keys[i].key_code[layer] & 0xFF00) == 0xE200)

#define SET_MODIFIER(mod)      active_key_regiser[0] |=  mod; Keyboard.set_modifier(active_key_regiser[0]);
#define RELEASE_MODIFIER(mod)  active_key_regiser[0] &= ~mod; Keyboard.set_modifier(active_key_regiser[0]);

//LED codes, used to turn the LEDs on/off
#define USB_LED_NUM_LOCK 0
#define USB_LED_CAPS_LOCK 1
#define USB_LED_SCROLL_LOCK 2
#define USB_LED_COMPOSE 3
#define USB_LED_KANA 4

//Functions to lock modifiers:
#define ADD_KEY_TO_PRESSED_REGISTER(i) \
  for(int x = 0;x<10;x++){\
    if(pressed_modifier_keys[x]==-1){\
      pressed_modifier_keys[x]=i;break;\
    }\
  }

#define REMOVE_KEY_FROM_PRESSED_REGISTER(i) \
  for(int x = 0;x<10;x++){\
    if(pressed_modifier_keys[x] == i){\
      pressed_modifier_keys[x]=-1;break;\
    }\
  }

  //for debugging
#define PRINT_PRESSED_SINGLE_ACTION_KEY_REGISTER
//  for(int x = 0;x<10;x++){
//    Serial.print(pressed_modifier_keys[x]);
//    Serial.print('\t');
//  }Serial.print('\n');


  //Key types are used to define the behavior of keys.
  typedef enum key_type {
    SINGLE_ACTION,
    SINGLE_ACTION_MODIFIER,
    DOUBLE_ACTION,
    DOUBLE_ACTION_NO_DELAY
  } KeyType;

  //Used to store the position of a switch in the struct Key.
  struct Rc {
    uint8_t c;
    uint8_t r;
  };

  //Stores all necessary information of one key.
  struct Key {
    KeyType type;

    //stores the key codes for all three layers
    uint16_t key_code[3];
    uint16_t modifier_code[3];

    //defines the index of the switch in the states array
    struct Rc first_switch_pos;
    struct Rc second_switch_pos;

    //Used to keep track of the current status of the key.
    bool double_press;

    //Stores the place of the pressed key in the active_key_register, each layer has one cell.
    uint8_t active_key_position[3];
  };

  //Stores the state of one switch in the states array.
  struct State {
    uint8_t state; // 1 or 0
    uint8_t last_state; // 1 or 0

    //Time when the state changed for the last time.
    unsigned long switch_state_changed_time;

    //Used to filter bouncing.
    unsigned long switch_bounce_time;
  };

#endif
