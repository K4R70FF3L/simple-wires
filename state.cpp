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
        setRGBLedByColor(unspecified);
        delay(500);
    }

    setRGBLedByColor(wireSetup[wireBeingSetUp]);

    if (wireBeingSetUp >= wireCount) {
        return STATE_READY;
    }
    return STATE_SETUP;
}

int ready()
{
    setRGBLedByColor(unspecified);
    return STATE_RUNNING;
}

boolean cutWires[] = { false, false, false, false, false, false };

int running()
{
    for (int index = 0; index < wireCount; ++index) {
        if (digitalRead(WIRES[index]) && !cutWires[index]) {
            if (index == wireToCut) {
                setRGBLedByColor(green);
                return STATE_FINISHED;
            } else {
                cutWires[index] = true;
                setRGBLedByColorForMillis(red, 1000);
            }
        }
    }
    return STATE_RUNNING;
}

int finished() { }
