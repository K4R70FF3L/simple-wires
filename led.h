#ifndef LED
#define LED

#include "rule.h"

void setRGBLedByColor(Color color);
void setRGBLedByColorForMillis(Color color, int millis);
void handleLeds();

#endif