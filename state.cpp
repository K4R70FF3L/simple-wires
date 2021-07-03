#include "constants.h"
#include "led.h"
#include "rule.h"
#include "state_init.h"
#include "stfu.h"

int wireCount;
int wireToCut;
bool serialOdd = true;
Rule solvingRule;
Color wireSetup[] = { unspecified, unspecified, unspecified, unspecified, unspecified, unspecified };

int initialize()
{
    randomSeed(42);
    wireCount = random(MIN_WIRES, MAX_WIRES + 1);
    solvingRule = determineSolvingRule(RULE_BOOK[wireCount - MIN_WIRES], serialOdd);
    setupWiresAccordingToRules(wireSetup, wireCount, RULE_BOOK[wireCount - MIN_WIRES], solvingRule, serialOdd);
    wireToCut = determineWireToCut(solvingRule, wireSetup);
    return STATE_SETUP;
}

int wireBeingSetUp = 0;

int setupWires()
{
    if (digitalRead(WIRES[wireBeingSetUp]) == LOW) {
        ++wireBeingSetUp;
    }

    setRGBLedByColor(wireSetup[wireBeingSetUp]);

    if (wireBeingSetUp >= wireCount) {
        return STATE_READY;
    }
    return STATE_SETUP;
}

int ready()
{
    if (digitalRead(WIRE_4) == HIGH) {
        setRGBLedByColor(blue);
    } else if (digitalRead(WIRE_4) == LOW) {
        setRGBLedByColor(white);
    }
    return STATE_READY;
}

int running() { }

int finished() { }
