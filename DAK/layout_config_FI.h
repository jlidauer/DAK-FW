/*
    DAK - is a firmware for Double Action Keyboards
    layout_config_FI.h - defines the layout of the keyboard

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

#ifndef LAYOUT
#define LAYOUT

/*
This file is used to define the functions of all keys on the keyboard. This
firmware is defined to support double action keys, thus, each key can have up
to two physical switches/buttons.

A key can work in three different modes (KeyType) called: ADDITIVE_ACTION, 
TOGGLE_ACTION, and DOUBLE_ACTION. The purpose of each mode is explained below:

ADDITIVE_ACTION
In this mode the first and second action are triggered independently. Thus,
when both actions are activated, the second action is added on top of the 
first action. This can be useful in cases where the second action enables an
additional modifier (e.g., first action: CTRL and second action: SHIFT).
Additionally, this mode can be used for traditional keys with only one action.
These keys have no added delays (the action is triggered immediately after
the state of the switch has changed).

TOGGLE_ACTION
In this mode only the first or the second action can be active at a time.
Thus, it is best suited for actions which have reversible functions (e.g., 
modifier keys). These keys have no added delays (the action is triggered 
immediately after the state of the switch has changed).
   
DOUBLE_ACTION
In this mode the first and second action are triggered separately, thus,
it can be used with actions keys which have irreversible functions 
(e.g., normal characters). The 1. action of these keys is delayed (as defined in 
constants.h) or triggered on the release of the key (which ever occurs first).


Note, all actions with only a modifier key, regardless of the key mode, lock down 
until all keys on the keyboard have been released. This is necessary as DOUBLE_ACTION
keys have a delayed first layer.

Additionally, each key has a separate FN-layer, which means that each key has two 
completely independent modes; one for the normal-layer and one for the FN-layer.
*/


// Short hands for often used modifiers.
#define ALTGR MODIFIERKEY_RIGHT_ALT//|MODIFIERKEY_RIGHT_CTRL
#define SHIFT MODIFIERKEY_SHIFT
#define CTRL  MODIFIERKEY_CTRL
#define ALT   MODIFIERKEY_ALT
#define GUI   MODIFIERKEY_GUI

// Define indices of FN-keys to activate the FN-layer
const uint8_t FN1[] = B58A;
const uint8_t FN2[] = B63A;

/*
To define a key the following syntax is used:
#define 
[KEY NAME] 
[KeyType (normal-layer)],
[KeyType (fn-layer)    ],
{[1. action key code  (normal-layer)], [2. action key code  (normal-layer)], [1. action key code  (fn-layer)], [2. action key code  (fn-layer)]},
{[1. action modifiers (normal-layer)], [2. action modifiers (normal-layer)], [1. action modifiers (fn-layer)], [2. action modifiers (fn-layer)]},
{[C1],[R1]},
{[C2],[R2]}

Where [C1] and [R1] are the indices of the switch for the 1. button in the states array
and [C2] and [R2] are the indices of the switch for the 2. button in the states array.

The states array keeps the current status of all switches. The array indices corresponds 
to the ROW_PINS and COLUMN_PINS arrays in hw_config.h

Note, key code/modifier "0" indicates: no action. 
*/

// Note, add all defined keys to the keys[] array after the key definitions.

// ROW 1:
#define K1   ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_ESC,KEY_SYSTEM_WAKE_UP,KEY_SYSTEM_SLEEP,0},{0,0,0,0},B1A,B2B //ESC sleep
#define K2   DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_TILDE, KEY_F1,0,0},{0,0,0,0},B2A,B2B //§
#define K3   DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_5, KEY_F2,0,0},{SHIFT,0,0,0},B3A,B3B //%
#define K4   DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_NON_US_BS, KEY_F3,0,0},{ALTGR,0,0,0},B4A,B4B //|
#define K5   DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_6, KEY_F4,0,0},{SHIFT,0,0,0},B5A,B5B //&
#define K6   DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_TILDE, KEY_F5,0,0},{SHIFT,0,0,0},B6A,B6B //½
#define K7   DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_EQUAL, KEY_F6,0,0},{0,0,0,0},B7A,B7B //´
#define K8   DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_EQUAL, KEY_F7,0,0},{SHIFT,0,0,0},B8A,B8B //`
#define K9   DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_E, KEY_F8,0,0},{ALTGR,0,0,0},B9A,B9B //€
#define K10  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_RIGHT_BRACE, KEY_F9,0,0},{ALTGR,0,0,0},B10A,B10B //~
#define K11  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_RIGHT_BRACE, KEY_F10,0,0},{SHIFT,0,0,0},B11A,B11B //^
#define K12  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_RIGHT_BRACE, KEY_F11,0,0},{0,0,0,0},B12A,B12B //¨
#define K13  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_3, KEY_F12,0,0},{ALTGR,0,0,0},B13A,B13B //£
#define K14  ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_DELETE,0,KEY_SYSTEM_POWER_DOWN,0},{0,0,0,0},B14A,B14B //DEL shut_down

//*******************************************//
// ROW 2:
#define K15  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_TAB,KEY_TAB,0,0},{0,SHIFT,0,0},B15A,B15B
#define K16  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_Q,KEY_2,KEY_TILDE,0},{0,ALTGR,0,0},B16A,B16B //@ §
#define K17  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_W,KEY_MINUS,0,0},{0,SHIFT,0,0},B17A,B17B //? up
#define K18  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_E,KEY_PERIOD,KEY_EQUAL,0},{0,SHIFT,0,0},B18A,B18B //: ´
#define K19  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_R,KEY_COMMA,KEY_EQUAL,0},{0,SHIFT,0,0},B19A,B19B //; `
#define K20  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_T,KEY_2,0,0},{0,SHIFT,0,0},B20A,B20B //"
#define K21  ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_PAGE_UP,0,0,0},{0,0,0,0},B21A,B21B // page up
#define K22  ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_HOME,0,0,0},{0,0,0,0},B22A,B22B // home
#define K23  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_Y,KEY_BACKSLASH,KEY_TILDE,0},{0,0,SHIFT,0},B23A,B23B //' ½
#define K24  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_U,KEY_7,KEY_RIGHT_BRACE,0},{0,0,0,0},B24A,B24B //7 ¨
#define K25  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_I,KEY_8,KEY_4,0},{0,0,SHIFT,0},B25A,B25B //8 ¤
#define K26  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_O,KEY_9,KEY_LEFT_BRACE,0},{0,0,0,0},B26A,B26B //9 å
#define K27  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_P,KEY_MINUS,KEY_3,0},{0,0,ALTGR,0},B27A,B27B //+ £
#define K28  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_3,KEY_4,0,0},{SHIFT,ALTGR,0,0},B28A,B28B //# $

//*******************************************//
// ROW 3:
#define K29  ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_CAPS_LOCK,0,0,0},{0,0,0,0},B29A,B29B 
#define K30  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_A,KEY_8,0,0},{0,ALTGR,0,0},B30A,B30B // [
#define K31  DOUBLE_ACTION,TOGGLE_ACTION,{KEY_S,KEY_9,0,0},{0,ALTGR,0,0},B31A,B31B // ]
#define K32  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_D,KEY_8,0,0},{0,SHIFT,0,0},B32A,B32B // (
#define K33  DOUBLE_ACTION,DOUBLE_ACTION,{KEY_F,KEY_9,0,0},{0,SHIFT,0,0},B33A,B33B // )
#define K34  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_G,KEY_7,0,0},{0,ALTGR,0,0},B34A,B34B // { 
#define K35  ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_PAGE_DOWN,0,0,0},{0,0,0,0},B35A,B35B // page down
#define K36  ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_END,0,0,0},{0,0,0,0},B36A,B36B // end
#define K37  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_H,KEY_0,0,0},{0,ALTGR,0,0},B37A,B37B // }
#define K38  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_J,KEY_4,KEY_NON_US_BS,0},{0,0,ALTGR,0},B38A,B38B // 4 |
#define K39  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_K,KEY_5,KEY_5,0},{0,0,SHIFT,0},B39A,B39B //5 %
#define K40  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_L,KEY_6,KEY_RIGHT_BRACE,0},{0,0,SHIFT,0},B40A,B40B // 6 ^ 
#define K41  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_SEMICOLON,KEY_0,0,0},{0,0,0,0},B41A,B41B //Ö 0
#define K42  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_QUOTE,KEY_1,0,0},{0,SHIFT,0,0},B42A,B42B //Ä !

//*******************************************//
// ROW 4:
#define K43  TOGGLE_ACTION,ADDITIVE_ACTION,{0,KEY_PRINTSCREEN,0,0},{SHIFT,0,SHIFT,0},B43A,B43B //SHIFT PRTSC
#define K44  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_Z,KEY_NON_US_BS,KEY_MEDIA_VOLUME_DEC,0},{0,0,0,0},B44A,B44B //<
#define K45  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_X,KEY_NON_US_BS,KEY_MEDIA_VOLUME_INC,0},{0,SHIFT,0,0},B45A,B45B //>
#define K46  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_C,KEY_0,KEY_MEDIA_MUTE,0},{0,SHIFT,0,0},B46A,B46B //=
#define K47  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_V,KEY_7,KEY_MEDIA_PAUSE,0},{0,SHIFT,0,0},B47A,B47B // /
#define K48  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_B,KEY_MINUS,KEY_MEDIA_PLAY,0},{0,ALTGR,0,0},B48A,B48B // BACKSLASH
#define K49  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_N,KEY_BACKSLASH,KEY_MEDIA_PREV_TRACK,0},{0,SHIFT,0,0},B49A,B49B //*
#define K50  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_M,KEY_1,KEY_MEDIA_NEXT_TRACK,0},{0,0,0,0},B50A,B50B //1
#define K51  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_COMMA,KEY_2,0,0},{0,0,0,0},B51A,B51B //2
#define K52  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_PERIOD,KEY_3,0,0},{0,0,0,0},B52A,B52B //3
#define K53  DOUBLE_ACTION,ADDITIVE_ACTION,{KEY_SLASH,KEY_SLASH,0,0},{MODIFIERKEY_RIGHT_SHIFT,0,0,0},B53A,B53B //_ -
#define K54  TOGGLE_ACTION,ADDITIVE_ACTION,{0,KEY_INSERT,0,0},{CTRL,0,0,0},B54A,B54B //SHIFT INSERT 

//*******************************************//
// ROW 5:
#define K55   ADDITIVE_ACTION,ADDITIVE_ACTION,{0,0,0,0},{CTRL,SHIFT,0,0},B55A,B55B //CTRL or CTRL+SHIFT
#define K56   ADDITIVE_ACTION,ADDITIVE_ACTION,{0,KEY_TAB,0,0},{GUI,0,0,0},B56A,B56B 
#define K57   ADDITIVE_ACTION,ADDITIVE_ACTION,{0,KEY_TAB,0,0},{ALT,0,0,0},B57A,B57B 
#define K58   ADDITIVE_ACTION,ADDITIVE_ACTION,{0,0,KEY_PAGE_UP,0},{0,0,CTRL,0},B58B,B58B  //FN left
#define K59   ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_SPACE,0,0,0},{0,0,0,0},B59A,B59B 
#define K60   ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_ENTER,0,0,0},{0,0,0,0},B60A,B60B 
#define K61   ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_BACKSPACE,0,0,0},{0,0,0,0},B61A,B61B 
#define K62   ADDITIVE_ACTION,ADDITIVE_ACTION,{0,0,0,0},{SHIFT,CTRL,SHIFT,CTRL},B62A,B62B // SHIFT or SHIFT+CTRL
#define K63   ADDITIVE_ACTION,ADDITIVE_ACTION,{0,0,KEY_PAGE_DOWN,0},{0,0,CTRL,0},B63B,B63B  // FN right
#define K64   ADDITIVE_ACTION,ADDITIVE_ACTION,{0,0,0,0},{MODIFIERKEY_RIGHT_ALT,0,0,0},B64A,B64B 
#define K65   ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_MENU,0,0,0},{0,0,0,0},B65A,B65B 
#define K66   ADDITIVE_ACTION,ADDITIVE_ACTION,{0,0,0,0},{MODIFIERKEY_RIGHT_CTRL,0,0,0},B66A,B66B 
                                                            
//*******************************************//
// Joystick
#define K67  ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_DOWN,0,KEY_DOWN,0},{0,0,GUI,0},B_down,{0,0} // Note, {0,0} refers to the same button as B1A, this is not a problem as long as neither second action is enabled (i.e., equals 0).
#define K68  ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_RIGHT,0,KEY_RIGHT,0},{0,0,GUI,0},B_right,{0,0}
#define K69  ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_DELETE,0,0,0},{0,0,0,0},B_center,{0,0}
#define K70  ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_UP,0,KEY_UP,0},{0,0,GUI,0},B_up,{0,0}
#define K71  ADDITIVE_ACTION,ADDITIVE_ACTION,{KEY_LEFT,0,KEY_LEFT,0},{0,0,GUI,0},B_left,{0,0}

// Define an constant array for storing all constant information of each key.
const struct KeyConst keys_const[] =
{
#ifndef DEBUG_PRINT_STATES_ARRAY // No keys are defined when debug mode is active.
{K1},
{K2},
{K3},
{K4},
{K5},
{K6},
{K7},
{K8},
{K9},
{K10},
{K11},
{K12},
{K13},
{K14},
{K15},
{K16},
{K17},
{K18},
{K19},
{K20},
{K21},
{K22},
{K23},
{K24},
{K25},
{K26},
{K27},
{K28},
{K29},
{K30},
{K31},
{K32},
{K33},
{K34},
{K35},
{K36},
{K37},
{K38},
{K39},
{K40},
{K41},
{K42},
{K43},
{K44},
{K45},
{K46},
{K47},
{K48},
{K49},
{K50},
{K51},
{K52},
{K53},
{K54},
{K55},
{K56},
{K57},
{K58},
{K59},
{K60},
{K61},
{K62},
{K63},
{K64},
{K65},
{K66},
{K67},
{K68},
{K69},
{K70},
{K71}
#endif
};

const int NUMBER_OF_KEYS = sizeof(keys_const)/sizeof(struct KeyConst);

// Define an array for storing all non-constant information of each key.
#define DEFAULT_VALUES false,{0},{NORMAL},DISABLED
struct Key keys[NUMBER_OF_KEYS] =
{
#ifndef DEBUG_PRINT_STATES_ARRAY // No keys are defined when debug mode is active.
{DEFAULT_VALUES}
#endif
};


#endif
