#include "stfu.h"

#ifndef CONSTANTS
#define CONSTANTS

// LEDs
const int LED_RED = 4;
const int LED_GREEN = 5;
const int LED_BLUE = 3;

const int LED_BRIGHTNESS_GREEN = 70;
const int LED_BRIGHTNESS_BLUE = 70;

const unsigned long LED_BLACK_BLINK_INTERVAL = 500;

// Wires
const int WIRE_1 = 6;
const int WIRE_2 = 7;
const int WIRE_3 = 8;
const int WIRE_4 = 9;
const int WIRE_5 = 10;
const int WIRE_6 = 11;
const int WIRES[] = { WIRE_1, WIRE_2, WIRE_3, WIRE_4, WIRE_5, WIRE_6 };

const int MIN_WIRES = 3;
const int MAX_WIRES = 6;

// States
const int STATE_INITIALIZE = 1;
const int STATE_SETUP = 2;
const int STATE_READY = 3;
const int STATE_RUNNING = 4;
const int STATE_FINISHED = 5;
const int STATE_INITIALIZE_ADDRESS = 6;

// Misc constants
const unsigned long DEBOUNCE_DELAY = 50;

const int RULE_PROBABILITY = 20;
const byte SERIAL_ODD_MASK = 0b1;

const byte MODULE_STATUS_SOLVED = 0b1;
const byte MODULE_STATUS_STRIKE = 0b10;

#endif
