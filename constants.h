#ifndef CONSTANTS
#define CONSTANTS

// LEDs
const int LED_RED = 2;
const int LED_GREEN = 3;
const int LED_BLUE = 4;
const int LED_YELLOW = 5;

// Wires
const int WIRE_1 = 6;
const int WIRE_2 = 7;
const int WIRE_3 = 8;
const int WIRE_4 = 9;
const int WIRE_5 = 10;
const int WIRE_6 = 11;
const int WIRES[] = { WIRE_1, WIRE_2, WIRE_3, WIRE_3, WIRE_4, WIRE_5, WIRE_6 };

const int MIN_WIRES = 3;
const int MAX_WIRES = 6;

// States
const int STATE_INITIALIZE = 1;
const int STATE_SETUP = 2;
const int STATE_READY = 3;
const int STATE_RUNNING = 4;
const int STATE_FINISHED = 5;

// Misc constants
const unsigned long DEBOUNCE_DELAY = 50;

const float RULE_PROBABILITY = 20;

#endif
