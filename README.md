# DAK
### Double Action Keyboard Firmware

This firmware is used for Double Action Keyboards with Teensy microcontrollers. 
Currently the firmware provides three layers _(first action, second action, fn layer)_.
The firmware is developed using the Arduino IDE with the Teensyduino add-on.

### What is a Double Action Keyboard?
A double action keyboard has switches that have two physical positions (two steps). Each key has two different functions that can be accessed without pressing modifier keys, this makes especially typing of special characters easier. For example when pressing a key 
only one step down the keyboard sends to the computer the key code of a normal key like `KEY_A` and if the same key is 
pressed two steps down it sends the key code of a special character, like `ALTGR + KEY_9`. 

More info can be found in the Wiki: [Building a Double Action Keyboard](https://github.com/jlidauer/DAK/wiki/Building-a-Double-Action-Keyboard).

### Compatible microcontrollers:
In principle all Teensy microcontrollers with a keyboard funtionality should work.

So far this firmware has been tested with the following microcontrollers:
- Teensy 3.2
- Teensy-LC

### How to use this firmware?
See the Wiki for instructions: [Getting Started](https://github.com/jlidauer/DAK/wiki/Getting-Started)

     
    
