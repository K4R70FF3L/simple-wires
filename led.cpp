#include "constants.h"
#include "rule.h"
#include "stfu.h"

unsigned long timestampSetRGB = 0;
unsigned long ledMilliseconds = 0;
boolean ledTimerActive = false;

void setRGBLedByColor(Color color)
{
    ledTimerActive = false;
    switch (color) {
    case red:
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, LOW);
        break;
    case blue:
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, HIGH);
        break;
    case yellow:
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_BLUE, LOW);
        break;
    case white:
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_BLUE, HIGH);
        break;
    case black:
        /* if (((millis() / LED_BLACK_BLINK_INTERVAL) % 2) == 1) {
            digitalWrite(LED_RED, LOW);
            digitalWrite(LED_GREEN, LOW);
            digitalWrite(LED_BLUE, LOW);
            break;
        } else {
            digitalWrite(LED_RED, HIGH);
            digitalWrite(LED_GREEN, HIGH);
            digitalWrite(LED_BLUE, HIGH);
            break;
        } */
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_BLUE, HIGH);
        break;
    case green:
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, HIGH);
        digitalWrite(LED_BLUE, LOW);
        break;
    default:
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, LOW);
    }
}

void setRGBLedByColorForMillis(Color color, int milliSeconds)
{
    setRGBLedByColor(color);
    ledMilliseconds = milliSeconds;
    timestampSetRGB = millis();
    ledTimerActive = true;
}

void handleLeds()
{
    if (ledTimerActive && millis() > (timestampSetRGB + ledMilliseconds)) {
        setRGBLedByColor(unspecified);
    }
}