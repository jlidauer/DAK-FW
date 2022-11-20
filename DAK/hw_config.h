/*
    DAK - is a firmware for Double Action Keyboards
    hw_config.h - defines the hardware setup
    
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

#ifndef HW_CONFIG
#define HW_CONFIG

// Select hardware version: 
#define DAK10
//#define DAK11
//#define DAK20
//#define DAK30

// If the DEBUG_PRINT_STATES_ARRAY is uncommented, will the states array be printed to the serial monitor. 
// This feature is useful to make sure that all switches are working properly. Use only for debugging.
// To enable the serialport set in the IDE: Tools -> USB type: -> 'Serial + Keyboard + Mouse + Joystic'

//#define DEBUG_PRINT_STATES_ARRAY // define to print the state of each switch (no key strokes will be sent)
//#define DEBUG_PRINT // define to enable verbose ouput of keyboard status.

// KEY MATRIX size:
#define ROWS 11
#define COLUMNS 14

// Use mux chip to set column active (can be used to reduce the number of IO pins)
#ifdef DAK30
#define USE_COLUMN_MUX 
#endif

#ifdef USE_COLUMN_MUX

const uint8_t MUX_COLUMN_INPUT_PIN = 9;

#define MUX_COLUMN_BITS 4
const uint8_t MUX_COLUMN_PINS[] = {8,7,5,6};// Pins in LSB

#endif

// Define IO pins according to hardware:
#if defined DAK10 || defined DAK20
// syntax:
// "#define [NAME] [pin number]"
// ROWS:
#define R0 22
#define R1 21
#define R2 20
#define R3 19
#define R4 18
#define R5 16
#define R6 14
#define R7 13
#define R8 26 
#define R9 15 
#define R10 12 

// COLUMNS:
#define C0 9
#define C1 8
#define C2 7
#define C3 6
#define C4 5
#define C5 4
#define C6 3
#define C7 2
#define C8 1
#define C9 0
#define C10 24
#define C11 25
#define C12 17
#define C13 23

// Output pins for LEDs
#define LED1 10 // CAPS LOCK
#define LED2 11 // FN LOCK

#elif defined DAK11

// ROWS:
#define R0 22
#define R1 20
#define R2 19
#define R3 18
#define R4 16
#define R5 15
#define R6 24
#define R7 25
#define R8 26 
#define R9 13 
#define R10 12 

// COLUMNS:
#define C0 9
#define C1 8
#define C2 7
#define C3 6
#define C4 5
#define C5 4
#define C6 3
#define C7 2
#define C8 1
#define C9 0
#define C10 14
#define C11 17
#define C12 21
#define C13 23

// Output pins for LEDs
#define LED1 10 // CAPS LOCK
#define LED2 11 // FN LOCK

#elif defined DAK30

// ROWS:
#define R0 14
#define R1 15
#define R2 16
#define R3 17
#define R4 18
#define R5 19
#define R6 20
#define R7 21
#define R8 22
#define R9 23
#define R10 2

// COLUMN pins or MUX values:
#define C0 0b0101
#define C1 0b0100
#define C2 0b0011
#define C3 0b0000
#define C4 0b1111
#define C5 0b1110
#define C6 0b1101
#define C7 0b1100
#define C8 0b1011
#define C9 0b1010
#define C10 0b1001
#define C11 0b1000
#define C12 0b0010
#define C13 0b0001

// Output pins for LEDs
#define LED1 12 // CAPS LOCK
#define LED2 3 // FN LOCK

#endif


//Add here all the rows and the columns defined above, from the smallest to the biggest.
const uint8_t ROW_PINS[] = {R0, R1, R2, R3, R4, R5, R6, R7, R8, R9, R10};
const uint8_t COLUMN_PINS[] = {C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13};

// Define all buttons in the matrix using indexes: {column, row}
// B*A corresponds the first button and B*B the second button in a single double action key.
#define B1A {0,0}
#define B1B {0,1}
#define B2A {1,0}
#define B2B {1,1}
#define B3A {2,0}
#define B3B {2,1}
#define B4A {3,0}
#define B4B {3,1}
#define B5A {4,0}
#define B5B {4,1}
#define B6A {5,0}
#define B6B {5,1}
#define B7A {6,0}
#define B7B {6,1}
#define B8A {7,0}
#define B8B {7,1}
#define B9A {8,0}
#define B9B {8,1}
#define B10A {9,0}
#define B10B {9,1}
#define B11A {10,0}
#define B11B {10,1}
#define B12A {11,0}
#define B12B {11,1}
#define B13A {12,0}
#define B13B {12,1}
#define B14A {13,0}
#define B14B {13,1}

#define B15A {0,2}
#define B15B {0,3}
#define B16A {1,2}
#define B16B {1,3}
#define B17A {2,2}
#define B17B {2,3}
#define B18A {3,2}
#define B18B {3,3}
#define B19A {4,2}
#define B19B {4,3}
#define B20A {5,2}
#define B20B {5,3}
#define B21A {6,2}
#define B21B {6,3}
#define B22A {7,2}
#define B22B {7,3}
#define B23A {8,2}
#define B23B {8,3}
#define B24A {9,2}
#define B24B {9,3}
#define B25A {10,2}
#define B25B {10,3}
#define B26A {11,2}
#define B26B {11,3}
#define B27A {12,2}
#define B27B {12,3}
#define B28A {13,2}
#define B28B {13,3}

#define B29A {0,4}
#define B29B {0,5}
#define B30A {1,4}
#define B30B {1,5}
#define B31A {2,4}
#define B31B {2,5}
#define B32A {3,4}
#define B32B {3,5}
#define B33A {4,4}
#define B33B {4,5}
#define B34A {5,4}
#define B34B {5,5}
#define B35A {6,4}
#define B35B {6,5}
#define B36A {7,4}
#define B36B {7,5}
#define B37A {8,4}
#define B37B {8,5}
#define B38A {9,4}
#define B38B {9,5}
#define B39A {10,4}
#define B39B {10,5}
#define B40A {11,4}
#define B40B {11,5}
#define B41A {12,4}
#define B41B {12,5}
#define B42A {13,4}
#define B42B {13,5}

#define B43A {0,6}
#define B43B {0,7}
#define B44A {1,6}
#define B44B {1,7}
#define B45A {2,6}
#define B45B {2,7}
#define B46A {3,6}
#define B46B {3,7}
#define B47A {4,6}
#define B47B {4,7}
#define B48A {5,6}
#define B48B {5,7}
// none {6,6}
// none {6,7}
// none {7,6}
// none {7,7}
#define B49A {8,6}
#define B49B {8,7}
#define B50A {9,6}
#define B50B {9,7}
#define B51A {10,6}
#define B51B {10,7}
#define B52A {11,6}
#define B52B {11,7}
#define B53A {12,6}
#define B53B {12,7}
#define B54A {13,6}
#define B54B {13,7}

#define B55A {0,8}
#define B55B {0,9}
#define B56A {1,8}
#define B56B {1,9}
#define B57A {2,8}
#define B57B {2,9}
// none {3,8}
// none {3,9}
#define B58A {4,8}
#define B58B {4,9}
#define B59A {5,8}
#define B59B {5,9}
#define B60A {6,9}
#define B60B {6,8}
#define B61A {7,9}
#define B61B {7,8}
#define B62A {8,8}
#define B62B {8,9}

#define B64A {11,8}
#define B64B {11,9}
#define B65A {12,8}
#define B65B {12,9}
#define B66A {13,8}
#define B66B {13,9}

#if defined DAK11

// Joystic
#define B_up {2,10}
#define B_down {4,10}
#define B_left {3,10}
#define B_right {0,10}
#define B_center {1,10}

// Right FN buttons
#define B63A {9,8}
#define B63B {9,9}

#elif defined DAK10 || defined DAK20

// Joystick
#define B_up {4,10}
#define B_down {0,10}
#define B_left {5,10}
#define B_right {1,10}
#define B_center {2,10}

// Right FN buttons
#define B63A {10,8}
#define B63B {10,9}

#elif defined DAK30

// Joystick
#define B_up {11,10}
#define B_down {8,10}
#define B_left {9,10}
#define B_right {7,10}
#define B_center {10,10}

// Right FN buttons
#define B63A {10,8}
#define B63B {10,9}

#endif

#endif
