#include "constants.h"
#include "led.h"
#include "rule.h"
#include "state_init.h"
#include <Arduino.h>
#include <Wire.h>

int wireCount;
int wireToCut;
int seed;
bool serialOdd;
byte address;
Rule solvingRule;
Color wireSetup[] = { unspecified, unspecified, unspecified, unspecified, unspecified, unspecified };
byte moduleSolved = 0;
bool strike = false;

bool gotConfigFromI2C = false;

void initializeFromI2C(int byteCount)
{
    seed = Wire.read() << 8;
    seed += Wire.read();
    serialOdd = (Wire.read() & SERIAL_ODD_MASK) > 0;
    randomSeed(seed);
    gotConfigFromI2C = true;
}

void getAddress(int byteCount)
{
    address = Wire.read();
    Wire.onReceive(initializeFromI2C);
    Wire.begin(address);
}

int initializeAddress()
{
    Wire.begin(8);
    Wire.onReceive(getAddress);
    return STATE_INITIALIZE;
}

int initialize()
{
    if (gotConfigFromI2C) {
        randomSeed(seed);
        wireCount = random(MIN_WIRES, MAX_WIRES + 1);
        solvingRule = determineSolvingRule(RULE_BOOK[wireCount - MIN_WIRES], serialOdd);
        setupWiresAccordingToRules(wireSetup, wireCount, RULE_BOOK[wireCount - MIN_WIRES], solvingRule, serialOdd);
        wireToCut = determineWireToCut(solvingRule, wireSetup);
        return STATE_SETUP;
    }
    return STATE_INITIALIZE;
}

void sendModuleStatus()
{
    byte status = moduleSolved;
    if (strike) {
        status |= MODULE_STATUS_STRIKE;
        strike = false;
    }
    Wire.write(status);
}

void receiveDuringGame(int byteCount) { }

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
        Wire.onRequest(sendModuleStatus);
        Wire.onReceive(receiveDuringGame);
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
                moduleSolved = MODULE_STATUS_SOLVED;
                return STATE_FINISHED;
            } else {
                cutWires[index] = true;
                strike = true;
                setRGBLedByColorForMillis(red, 1000);
            }
        }
    }
    return STATE_RUNNING;
}

int finished() { return STATE_FINISHED; }
