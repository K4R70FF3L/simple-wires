#ifndef STATE_INIT
#define STATE_INIT

#include "rule.h"

void setupWiresAccordingToRules(Color wireSetup[], int wireCount, RuleSet rules, Rule& solvingRule, bool serialOdd);

Rule determineSolvingRule(RuleSet rules, bool serialOdd);

bool ruleApplies(Rule rule, Color wireSetup[], bool serialOdd);

int determineWireToCut(Rule solvingRule, Color wireSetup[]);

#endif