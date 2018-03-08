/*
    DAK - is a firmware for Double Action Keyboards
    key_matrix.h - contains the IO pin connections
    
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

#ifndef KEY_MATRIX
#define KEY_MATRIX

//If the DEBUG_PRINT_STATES_ARRAY is uncommented, will the states array be printed to the serial monitor. 
//This feature is useful to make sure that all switches are working properly. Use only for debugging.
//To enable the serialport set in the IDE: Tools -> USB type: -> 'Serial + Keyboard + Mouse + Joystic'

//#define DEBUG_PRINT_STATES_ARRAY

//KEY MATRIX size:
#define ROWS 11
#define COLUMNS 14

//OI pins:

//syntax:
//"#define [NAME] [pin number]"
//ROWS:
#define R1 22
#define R2 21
#define R3 20
#define R4 19
#define R5 18
#define R6 16
#define R7 14
#define R8 13
#define R9 26 
#define R10 15 
#define R11 12 

//COLUMNS:
#define C1 9
#define C2 8
#define C3 7
#define C4 6
#define C5 5
#define C6 4
#define C7 3
#define C8 2
#define C9 1
#define C10 0
#define C11 24
#define C12 25
#define C13 17
#define C14 23

//Output pins for LEDs
#define LED1 10  //CAPS LOCK
#define LED2 11 //FN LOCK

//Add here all the rows and the columns defined above, in order from the smallest to the biggest.
const uint8_t ROW_PINS[] = {R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11};
const uint8_t COLUMN_PINS[] = {C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14};

#endif
