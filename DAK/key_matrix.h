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
#define ROWS 9
#define COLUMNS 14

//OI pins:

//syntax:
//"#define [NAME] [pin number]"
//ROWS:
#define R1 21
#define R2 20
#define R3 19
#define R4 18
#define R5 17
#define R6 16
#define R7 15
#define R8 14
#define R9 12 

//COLUMNS:
#define C1 11
#define C2 10
#define C3 9
#define C4 8
#define C5 1
#define C6 7
#define C7 2
#define C8 6
#define C9 22
#define C10 5
#define C11 4
#define C12 3
#define C13 13
#define C14 23

//Output pins for LEDs
#define LED1 0  //CAPS LOCK
#define LED2 24 //FN LOCK

//Add here all the rows and the columns defined above, in order from the smallest to the biggest.
const uint8_t ROW_PINS[] = {R1, R2, R3, R4, R5, R6, R7, R8, R9};
const uint8_t COLUMN_PINS[] = {C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, C13, C14};

#endif
