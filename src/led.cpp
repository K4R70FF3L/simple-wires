#include "led.h"
#include "constants.h"
#include "rule.h"
#include <Arduino.h>

unsigned long timestampSetRGB = 0;
unsigned long ledMilliseconds = 0;
Color currentLedColor = unspecified;
boolean ledTimerActive = false;

void setRGBLedByColor(Color color)
{
    ledTimerActive = false;
    currentLedColor = color;
    handleLeds();
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

    switch (currentLedColor) {
    case red:
        digitalWrite(LED_RED, HIGH);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, LOW);
        break;
    case blue:
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        analogWrite(LED_BLUE, LED_BRIGHTNESS_BLUE);
        break;
    case yellow:
        digitalWrite(LED_RED, HIGH);
        analogWrite(LED_GREEN, LED_BRIGHTNESS_GREEN);
        digitalWrite(LED_BLUE, LOW);
        break;
    case white:
        digitalWrite(LED_RED, HIGH);
        analogWrite(LED_GREEN, LED_BRIGHTNESS_GREEN);
        analogWrite(LED_BLUE, LED_BRIGHTNESS_BLUE);
        break;
    case black:
        if (((millis() / LED_BLACK_BLINK_INTERVAL) % 2) == 1) {
            digitalWrite(LED_RED, LOW);
            digitalWrite(LED_GREEN, LOW);
            digitalWrite(LED_BLUE, LOW);
            break;
        } else {
            digitalWrite(LED_RED, HIGH);
            analogWrite(LED_GREEN, LED_BRIGHTNESS_GREEN);
            analogWrite(LED_BLUE, LED_BRIGHTNESS_BLUE);
            break;
        }
        break;
    case green:
        digitalWrite(LED_RED, LOW);
        analogWrite(LED_GREEN, LED_BRIGHTNESS_GREEN);
        digitalWrite(LED_BLUE, LOW);
        break;
    default:
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, LOW);
    }
}