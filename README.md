# DAK
### Double Action Keyboard Firmware
This firmware is used for Double Action Keyboards with Teensy microcontrollers. Currently the firmware provides two independed layers _(normal-layer and FN-layer)_, both of these layers support double action _(first action, second action)_. This means that each double action key can be configured to have up to four independent actions. The firmware is developed using the Arduino IDE with the Teensyduino add-on.

### Double Action Keyboard PCB V1.0
An example implementation a double action keyboard PCB can be found in the PCB directory.

### What is a Double Action Keyboard?
A double action keyboard has switches that have two physical positions (two steps). Each key has two different functions that can be triggered without pressing modifier keys, this makes typing of special characters easier. For example, when pressing a key one step down, the keyboard could send a normal key stroke (e.g., `KEY_A`), and if the same key would be pressed two steps down instead, the keyboard could send the key combination of a special character (e.g., `ALTGR + KEY_9`). 

More info can be found in the Wiki: [Building a Double Action Keyboard](https://github.com/jlidauer/DAK/wiki/Building-a-Double-Action-Keyboard).

### Compatible microcontrollers:
In principle all Teensy microcontrollers with keyboard funtionality should work.

The firmware has been tested with the following microcontrollers:
- Teensy 3.2
- Teensy-LC

### How to use this firmware?
See the Wiki for instructions: [Getting Started](https://github.com/jlidauer/DAK/wiki/Getting-Started)