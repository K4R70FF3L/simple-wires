#include "constants.h"
#include "rule.h"
#include "state_init.h"
#include "state_setup.h"
#include "stfu.h"

namespace State {

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

int setup() { }

int ready() { }

int running() { }

int finished() { }

} // namespace State