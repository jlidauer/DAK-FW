/*
    DAK - is a firmware for Double Action Keyboards
    layout_FI.h - defines the layout of the keyboard

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
//This layout uses F-keys for special characters.
#ifndef LAYOUT
#define LAYOUT

/*KeyTypes that are used to define the functionality of the keys:
  SINGLE_ACTION             for "normal keys" with only one action + FN layer
  SINGLE_ACTION_MODIFIER    for single action modifier keys, these keys lock down when other keys are pressed simultaneously
  DOUBLE_ACTION             for double action keys which have irreversible functions e.g. normal characters
  DOUBLE_ACTION_NO_DELAY    for double action keys which have reversible functions e.g. modifier keys, they do also lock down
*/

//Update this value so that is equals to the numbers of keys in the keys array below:
const int NUMBER_OF_KEYS = 69;

//These macros make often used modifier easier to use.
#define ALTGR MODIFIERKEY_RIGHT_ALT|MODIFIERKEY_CTRL
#define SHIFT MODIFIERKEY_SHIFT
#define CTRL  MODIFIERKEY_CTRL
#define ALT   MODIFIERKEY_ALT
#define GUI   MODIFIERKEY_GUI

//FN switch indices in the states array. (0,0) is the up left corner.
#define FN1_ROW 8
#define FN1_COL 4
#define FN2_ROW 8
#define FN2_COL 10

/*
  The following line presents how to define the funtionality of one key:
  #define [NAME] [KeyType],{[1.L key code], [2.L key code], [3.L key code]},{[1.L modifiers], [2.L modifiers], [3.L modifiers]},{[C1],[R1]},{[C2],[R1]}

  Where [C1] and [R1] are the indices of the switch for the 1. layer in the states array
  and [C2] and [R2] are the indices of the switch for the 2. layer in the states array.

  The states array keeps the current status of all switches. The array corresponds to the
  key matrix defined in key_matrix.h. The indices can be calculated using the following
  formula: index = [ROW or COLUMN number] - 1
*/

//Add all here defined keys to the keys[] array below.

//ROW 1:
#define C1R1  SINGLE_ACTION,{KEY_ESC,0,KEY_SYSTEM_SLEEP},{0,0,0},{0,0},{0,1}//ESC sleep
#define C2R1  DOUBLE_ACTION,{KEY_TILDE, KEY_F1,0},{0,0,0},{1,0},{1,1}//§
#define C3R1  DOUBLE_ACTION,{KEY_5, KEY_F2,0},{SHIFT,0,0},{2,0},{2,1}//%
#define C4R1  DOUBLE_ACTION,{KEY_NON_US_BS, KEY_F3,0},{ALTGR,0,0},{3,0},{3,1}//|
#define C5R1  DOUBLE_ACTION,{KEY_6, KEY_F4,0},{SHIFT,0,0},{4,0},{4,1}//&
#define C6R1  DOUBLE_ACTION,{KEY_TILDE, KEY_F5,0},{SHIFT,0,0},{5,0},{5,1}//½
#define C7R1  DOUBLE_ACTION,{KEY_EQUAL, KEY_F6,0},{0,0,0},{6,0},{6,1}//´
#define C8R1  DOUBLE_ACTION,{KEY_EQUAL, KEY_F7,0},{SHIFT,0,0},{7,0},{7,1}//`
#define C9R1  DOUBLE_ACTION,{0, KEY_F8,0},{0,0,0},{8,0},{8,1}//
#define C10R1 DOUBLE_ACTION,{KEY_RIGHT_BRACE, KEY_F9,0},{ALTGR,0,0},{9,0},{9,1}//~
#define C11R1 DOUBLE_ACTION,{KEY_RIGHT_BRACE, KEY_F10,0},{SHIFT,0,0},{10,0},{10,1}//^
#define C12R1 DOUBLE_ACTION,{KEY_RIGHT_BRACE, KEY_F11,0},{0,0,0},{11,0},{11,1}//¨
#define C13R1 DOUBLE_ACTION,{KEY_3, KEY_F12,0},{ALTGR,0,0},{12,0},{12,1}//£
#define C14R1 SINGLE_ACTION,{KEY_DELETE,0,KEY_SYSTEM_POWER_DOWN},{0,0,0},{13,0},{13,1}//DEL shut_down

//*******************************************//
//ROW 2:
#define C1R2  SINGLE_ACTION,{KEY_TAB,0,0},{0,0,0},{0,2},{0,0}
#define C2R2  DOUBLE_ACTION,{KEY_Q,KEY_2,KEY_TILDE},{0,ALTGR,0},{1,2},{1,3}//@ §
#define C3R2  DOUBLE_ACTION,{KEY_W,KEY_MINUS,KEY_UP},{0,SHIFT,0},{2,2},{2,3}//? up
#define C4R2  DOUBLE_ACTION,{KEY_E,KEY_PERIOD,KEY_EQUAL},{0,SHIFT,0},{3,2},{3,3}//: ´
#define C5R2  DOUBLE_ACTION,{KEY_R,KEY_COMMA,KEY_EQUAL},{0,SHIFT,0},{4,2},{4,3}//; `
#define C6R2  DOUBLE_ACTION,{KEY_T,KEY_2,0},{0,SHIFT,0},{5,2},{5,3}//"
#define C7R2  DOUBLE_ACTION,{KEY_PAGE_UP,KEY_V,0},{0,CTRL,0},{6,2},{6,3}
#define C8R2  SINGLE_ACTION,{KEY_HOME,0,0},{0,0,0},{7,2},{0,0}
#define C9R2  DOUBLE_ACTION,{KEY_Y,KEY_BACKSLASH,KEY_TILDE},{0,0,SHIFT},{8,2},{8,3}//' ½
#define C10R2 DOUBLE_ACTION,{KEY_U,KEY_7,KEY_RIGHT_BRACE},{0,0,0},{9,2},{9,3}//7 ¨
#define C11R2 DOUBLE_ACTION,{KEY_I,KEY_8,KEY_4},{0,0,SHIFT},{10,2},{10,3}//8 ¤
#define C12R2 DOUBLE_ACTION,{KEY_O,KEY_9,KEY_LEFT_BRACE},{0,0,0},{11,2},{11,3}//9 å
#define C13R2 DOUBLE_ACTION,{KEY_P,KEY_MINUS,KEY_3},{0,0,ALTGR},{12,2},{12,3}//+ £
#define C14R2 DOUBLE_ACTION,{KEY_3,KEY_4,0},{SHIFT,ALTGR,0},{13,2},{13,3}//# $

//*******************************************//
//ROW 3:
#define C1R3  SINGLE_ACTION,{KEY_CAPS_LOCK,0,0},{0,0,0},{0,4},{0,0}
#define C2R3  DOUBLE_ACTION,{KEY_A,KEY_8,0},{0,ALTGR,0},{1,4},{1,5}//[
#define C3R3  DOUBLE_ACTION,{KEY_S,KEY_9,0},{0,ALTGR,0},{2,4},{2,5}//]
#define C4R3  DOUBLE_ACTION,{KEY_D,KEY_8,0},{0,SHIFT,0},{3,4},{3,5}//(
#define C5R3  DOUBLE_ACTION,{KEY_F,KEY_9,KEY_6},{0,SHIFT,SHIFT},{4,4},{4,5}//) &
#define C6R3  DOUBLE_ACTION,{KEY_G,KEY_7,KEY_RIGHT_BRACE},{0,ALTGR,ALTGR},{5,4},{5,5}//{ ~
#define C7R3  DOUBLE_ACTION,{KEY_PAGE_DOWN,KEY_C,0},{0,CTRL,0},{6,4},{6,5}
#define C8R3  SINGLE_ACTION,{KEY_END,0,0},{0,0,0},{7,4},{0,0}
#define C9R3  DOUBLE_ACTION,{KEY_H,KEY_0,KEY_RIGHT_BRACE},{0,ALTGR,SHIFT},{8,4},{8,5}//} ^
#define C10R3 DOUBLE_ACTION,{KEY_J,KEY_4,KEY_NON_US_BS},{0,0,ALTGR},{9,4},{9,5}//4 |
#define C11R3 DOUBLE_ACTION,{KEY_K,KEY_5,KEY_5},{0,0,SHIFT},{10,4},{10,5}//5 %
#define C12R3 DOUBLE_ACTION,{KEY_L,KEY_6,0},{0,0,0},{11,4},{11,5}//6 
#define C13R3 DOUBLE_ACTION,{KEY_SEMICOLON,KEY_0,0},{0,0,0},{12,4},{12,5}//Ö 0
#define C14R3 DOUBLE_ACTION,{KEY_QUOTE,KEY_1,0},{0,SHIFT,0},{13,4},{13,5}//Ä !

//*******************************************//
//ROW 4:
#define C1R4  DOUBLE_ACTION_NO_DELAY,{0,KEY_PRINTSCREEN,0},{CTRL,0,0},{0,6},{0,7}//SHIFT PRTSC
#define C2R4  DOUBLE_ACTION,{KEY_Z,KEY_NON_US_BS,KEY_MEDIA_VOLUME_DEC},{0,0,0},{1,6},{1,7}//<
#define C3R4  DOUBLE_ACTION,{KEY_X,KEY_NON_US_BS,KEY_MEDIA_VOLUME_INC},{0,SHIFT,0},{2,6},{2,7}//>
#define C4R4  DOUBLE_ACTION,{KEY_C,KEY_0,KEY_MEDIA_MUTE},{0,SHIFT,0},{3,6},{3,7}//=
#define C5R4  DOUBLE_ACTION,{KEY_V,KEY_7,KEY_MEDIA_PAUSE},{0,SHIFT,0},{4,6},{4,7}// /
#define C6R4  DOUBLE_ACTION,{KEY_B,KEY_MINUS,KEY_MEDIA_PLAY},{0,ALTGR,0},{5,6},{5,7}// BACKSLASH
//#define C7R4
//#define C8R4
#define C9R4  DOUBLE_ACTION,{KEY_N,KEY_BACKSLASH,KEY_MEDIA_PREV_TRACK},{0,SHIFT,0},{8,6},{8,7}//*
#define C10R4 DOUBLE_ACTION,{KEY_M,KEY_1,KEY_MEDIA_NEXT_TRACK},{0,0,0},{9,6},{9,7}//1
#define C11R4 DOUBLE_ACTION,{KEY_COMMA,KEY_2,0},{0,0,0},{10,6},{10,7}//2
#define C12R4 DOUBLE_ACTION,{KEY_PERIOD,KEY_3,0},{0,0,0},{11,6},{11,7}//3
#define C13R4 DOUBLE_ACTION,{KEY_SLASH,KEY_SLASH,0},{MODIFIERKEY_RIGHT_SHIFT,0,0},{12,6},{12,7}//_ -
#define C14R4 DOUBLE_ACTION_NO_DELAY,{0,KEY_INSERT,0},{CTRL,0,0},{13,6},{13,7}//SHIFT INSERT 

//*******************************************//
//ROW 5:
#define C1R5  SINGLE_ACTION_MODIFIER,{0,0,0},{CTRL,0,0},{0,8},{0,0}//CTRL
#define C2R5  SINGLE_ACTION_MODIFIER,{0,0,0},{GUI,0,0},{1,8},{0,0}
#define C3R5  SINGLE_ACTION_MODIFIER,{0,0,0},{ALT,0,0},{2,8},{0,0}
//#define C4R5  //
//#define C5R5  //FN
#define C6R5  SINGLE_ACTION,{KEY_SPACE,0,0},{0,0,0},{5,8},{0,0}
#define C7R5  SINGLE_ACTION,{KEY_ENTER,0,0},{0,0,0},{6,9},{0,0}
#define C8R5  SINGLE_ACTION,{KEY_BACKSPACE,KEY_BACKSPACE,0},{0,0,0},{7,9},{7,8}
#define C9R5  SINGLE_ACTION_MODIFIER,{0,0,0},{SHIFT,0,0},{8,8},{0,0}
//#define C10R5  //FN
//#define C11R5 
#define C12R5 SINGLE_ACTION_MODIFIER,{0,0,0},{MODIFIERKEY_RIGHT_ALT,0,0},{11,8},{0,0}
#define C13R5 SINGLE_ACTION,{KEY_MENU,0,0},{0,0,0},{12,8},{0,0}
#define C14R5 SINGLE_ACTION_MODIFIER,{0,0,0},{MODIFIERKEY_RIGHT_CTRL,0,0},{13,8},{0,0}

//*******************************************//
//ROW 6:
//#define C1R6
//#define C2R6
#define C3R6  SINGLE_ACTION,{KEY_DOWN,0,KEY_DOWN},{0,0,GUI},{0,10},{0,0}
#define C4R6  SINGLE_ACTION,{KEY_RIGHT,0,KEY_RIGHT},{0,0,GUI},{1,10},{0,0}
//#define C5R6
#define C6R6  SINGLE_ACTION,{KEY_DELETE,0,0},{0,0,0},{2,10},{0,0}
#define C7R6  SINGLE_ACTION,{KEY_UP,0,KEY_UP},{0,0,GUI},{4,10},{0,0}
#define C8R6  SINGLE_ACTION,{KEY_LEFT,0,KEY_LEFT},{0,0,GUI},{5,10},{0,0}
//#define C9R6
//#define C10R6
//#define C11R6
//#define C12R6
//#define C13R6
//#define C14R6


#define DEFAULT_VALUES false,{0}

//Add here all keys defined above, the order they are added is irrelevant.
struct Key keys[NUMBER_OF_KEYS] =
{
#ifndef DEBUG_PRINT_STATES_ARRAY //No keys are defined when debug mode is active.
{C1R1,  DEFAULT_VALUES},
{C2R1,  DEFAULT_VALUES},
{C3R1,  DEFAULT_VALUES},
{C4R1,  DEFAULT_VALUES},
{C5R1,  DEFAULT_VALUES},
{C6R1,  DEFAULT_VALUES},
{C7R1,  DEFAULT_VALUES},
{C8R1,  DEFAULT_VALUES},
{C9R1,  DEFAULT_VALUES},
{C10R1, DEFAULT_VALUES},
{C11R1, DEFAULT_VALUES},
{C12R1, DEFAULT_VALUES},
{C13R1, DEFAULT_VALUES},
{C14R1, DEFAULT_VALUES},
{C1R2,  DEFAULT_VALUES},
{C2R2,  DEFAULT_VALUES},
{C3R2,  DEFAULT_VALUES},
{C4R2,  DEFAULT_VALUES},
{C5R2,  DEFAULT_VALUES},
{C6R2,  DEFAULT_VALUES},
{C7R2,  DEFAULT_VALUES},
{C8R2,  DEFAULT_VALUES},
{C9R2,  DEFAULT_VALUES},
{C10R2, DEFAULT_VALUES},
{C11R2, DEFAULT_VALUES},
{C12R2, DEFAULT_VALUES},
{C13R2, DEFAULT_VALUES},
{C14R2, DEFAULT_VALUES},
{C1R3,  DEFAULT_VALUES},
{C2R3,  DEFAULT_VALUES},
{C3R3,  DEFAULT_VALUES},
{C4R3,  DEFAULT_VALUES},
{C5R3,  DEFAULT_VALUES},
{C6R3,  DEFAULT_VALUES},
{C7R3,  DEFAULT_VALUES},
{C8R3,  DEFAULT_VALUES},
{C9R3,  DEFAULT_VALUES},
{C10R3, DEFAULT_VALUES},
{C11R3, DEFAULT_VALUES},
{C12R3, DEFAULT_VALUES},
{C13R3, DEFAULT_VALUES},
{C14R3, DEFAULT_VALUES},
{C1R4,  DEFAULT_VALUES},
{C2R4,  DEFAULT_VALUES},
{C3R4,  DEFAULT_VALUES},
{C4R4,  DEFAULT_VALUES},
{C5R4,  DEFAULT_VALUES},
{C6R4,  DEFAULT_VALUES},
{C9R4,  DEFAULT_VALUES},
{C10R4, DEFAULT_VALUES},
{C11R4, DEFAULT_VALUES},
{C12R4, DEFAULT_VALUES},
{C13R4, DEFAULT_VALUES},
{C14R4, DEFAULT_VALUES},
{C1R5,  DEFAULT_VALUES},
{C2R5,  DEFAULT_VALUES},
{C3R5,  DEFAULT_VALUES},
{C6R5,  DEFAULT_VALUES},
{C7R5,  DEFAULT_VALUES},
{C8R5,  DEFAULT_VALUES},
{C9R5,  DEFAULT_VALUES},
{C12R5, DEFAULT_VALUES},
{C13R5, DEFAULT_VALUES},
{C14R5, DEFAULT_VALUES},
{C3R6,  DEFAULT_VALUES},
{C4R6,  DEFAULT_VALUES},
{C6R6,  DEFAULT_VALUES},
{C7R6,  DEFAULT_VALUES},
{C8R6,  DEFAULT_VALUES}
#endif
};

#endif
