#include "constants.h"
#include "state.h"
#include "stfu.h"

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
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Turn LEDs off for now
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_BUILTIN, LOW);

  // Set beginning state
  state = STATE_SETUP;
}

void loop()
{

  switch (state)
  {
  case STATE_INITIALIZE:
    state = State::initialize();
    break;
  case STATE_SETUP:
    state = State::setup();
    break;
  case STATE_READY:
    state = State::ready();
    break;
  case STATE_RUNNING:
    state = State::running();
    break;
  case STATE_FINISHED:
    state = State::finished();
    break;
  }
  /* int reading = digitalRead(READ_PIN);

  if (reading != lastReadState)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY)
  {
    if (reading != readState)
    {
      readState = reading;

      if (readState == HIGH)
      {
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, LOW);
        digitalWrite(LED_YELLOW, LOW);
      }
    }
  }

  lastReadState = reading; */
}
