#include "constants.h"
#include "led.h"
#include "state.h"
#include "stfu.h"
#include <Wire.h>

// Variables
int state;
unsigned long lastDebounceTime = 0;
int lastReadState = LOW;
int readState;

void setup()
{
    // Setup wire pins, need to be connected to GND
    pinMode(WIRE_1, INPUT_PULLUP);
    pinMode(WIRE_2, INPUT_PULLUP);
    pinMode(WIRE_3, INPUT_PULLUP);
    pinMode(WIRE_4, INPUT_PULLUP);
    pinMode(WIRE_5, INPUT_PULLUP);
    pinMode(WIRE_6, INPUT_PULLUP);

    // Setup LEDs
    // TODO replace with RGB LED upon arrival
    pinMode(LED_RED, OUTPUT);
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);

    // Turn LEDs off for now
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
    digitalWrite(LED_BUILTIN, LOW);

    // Set beginning state
    state = STATE_INITIALIZE_ADDRESS;
}

void loop()
{

    switch (state) {
    case STATE_INITIALIZE_ADDRESS:
        state = initializeAddress();
        break;
    case STATE_INITIALIZE:
        state = initialize();
        break;
    case STATE_SETUP:
        state = setupWires();
        break;
    case STATE_READY:
        state = ready();
        break;
    case STATE_RUNNING:
        state = running();
        break;
    case STATE_FINISHED:
        state = finished();
        break;
    }
    handleLeds();
}
