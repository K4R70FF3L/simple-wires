#include "constants.h"
#include "led.h"
#include "rule.h"
#include <Arduino.h>

bool ruleApplies(Rule rule, Color wireSetup[], bool serialOdd)
{
    if (rule.additionalRule != nullptr) {
        if (!ruleApplies(*rule.additionalRule, wireSetup, serialOdd)) {
            return false;
        }
    }

    // TODO for anything beyond default rules, this is going to need a major overhaul
    if (rule.color == serial) {
        // Handle serial rules
        return serialOdd;
    } else if (rule.position >= 0) {
        // Handle rules specifying color at position
        return wireSetup[rule.position] == rule.color;
    } else {
        // Handle rules specifying wire count of color
        int wireCount = 0;
        // Count wires of color specified in rule
        for (int index = 0; index < 6; ++index) {
            wireCount += wireSetup[index] == rule.color ? 1 : 0;
        }
        // Evaluate wire count according to countExact
        if (rule.countExact == 0 && wireCount != rule.count) {
            return false;
        } else if (rule.countExact == 1 && wireCount < rule.count) {
            return false;
        } else if (rule.countExact == -1 && wireCount > rule.count) {
            return false;
        } else if (rule.countExact == 2 && wireCount <= rule.count) {
            return false;
        } else if (rule.countExact == -2 && wireCount >= rule.count) {
            return false;
        }
    }

    return true;
}

void setupWiresAccordingToRules(Color wireSetup[], int wireCount, RuleSet rules, Rule& solvingRule, bool serialOdd)
{
    Color colors[] = { red, blue, yellow, white, black };
    for (int index = 0; index < wireCount; ++index) {
        wireSetup[index] = colors[random(5)];
    }
    bool changed[] = { false, false, false, false, false, false };

    Rule* solvingRulePart = &solvingRule;
    while (solvingRulePart != nullptr) {
        if (solvingRulePart->color == serial || solvingRulePart->color == unspecified) {
            // Nothing to do for these rules
        } else if (solvingRulePart->position > -1) {
            wireSetup[solvingRulePart->position] = solvingRulePart->color;
            changed[solvingRulePart->position] = true;
        } else {
            int wiresOfColor = 0;
            // Count wires of color specified in rule
            for (int index = 0; index < 6; ++index) {
                if (wireSetup[index] == solvingRulePart->color) {
                    ++wiresOfColor;
                    changed[index] = true;
                }
            }

            if (solvingRulePart->countExact == 0 && wiresOfColor != solvingRulePart->count) {
                while (wiresOfColor > solvingRulePart->count) {
                    for (int index = 0; index < wireCount; ++index) {
                        if (wireSetup[index] == solvingRulePart->color) {
                            wireSetup[index] = green;
                            --wiresOfColor;
                            changed[index] = false;
                            break;
                        }
                    }
                }
                while (wiresOfColor < solvingRulePart->count) {
                    for (int index = 0; index < wireCount; ++index) {
                        if (!changed[index] && wireSetup[index] != solvingRulePart->color) {
                            wireSetup[index] = solvingRulePart->color;
                            ++wiresOfColor;
                            changed[index] = true;
                            break;
                        }
                    }
                }
            } else if (solvingRulePart->countExact == 1 && wiresOfColor < solvingRulePart->count) {
                while (wiresOfColor < solvingRulePart->count) {
                    for (int index = 0; index < wireCount; ++index) {
                        if (!changed[index] && wireSetup[index] != solvingRulePart->color) {
                            wireSetup[index] = solvingRulePart->color;
                            ++wiresOfColor;
                            changed[index] = true;
                            break;
                        }
                    }
                }
            } else if (solvingRulePart->countExact == -1 && wiresOfColor > solvingRulePart->count) {
                while (wiresOfColor > solvingRulePart->count) {
                    for (int index = 0; index < wireCount; ++index) {
                        if (wireSetup[index] == solvingRulePart->color) {
                            wireSetup[index] = green;
                            --wiresOfColor;
                            changed[index] = false;
                            break;
                        }
                    }
                }
            } else if (solvingRulePart->countExact == 2 && wiresOfColor <= solvingRulePart->count) {
                while (wiresOfColor <= solvingRulePart->count) {
                    for (int index = 0; index < wireCount; ++index) {
                        if (!changed[index] && wireSetup[index] != solvingRulePart->color) {
                            wireSetup[index] = solvingRulePart->color;
                            ++wiresOfColor;
                            changed[index] = true;
                            break;
                        }
                    }
                }
            } else if (solvingRulePart->countExact == -2 && wiresOfColor >= solvingRulePart->count) {
                while (wiresOfColor >= solvingRulePart->count) {
                    for (int index = 0; index < wireCount; ++index) {
                        if (wireSetup[index] == solvingRulePart->color) {
                            wireSetup[index] = green;
                            --wiresOfColor;
                            changed[index] = false;
                            break;
                        }
                    }
                }
            }
        }
        solvingRulePart = solvingRulePart->additionalRule;
    }

    while (rules.rule != solvingRule) {
        while (ruleApplies(rules.rule, wireSetup, serialOdd)) {
            if (rules.rule.position >= 0) {
                wireSetup[rules.rule.position] = green;
            } else if (rules.rule.countExact < 0) {
                for (int index = 0; index < wireCount; ++index) {
                    if (!changed[index] && wireSetup[index] != rules.rule.color) {
                        wireSetup[index] = rules.rule.color;
                        changed[index] = true;
                        break;
                    }
                }
            } else if (rules.rule.countExact > 0) {
                for (int index = 0; index < wireCount; ++index) {
                    if (!changed[index] && wireSetup[index] == rules.rule.color) {
                        wireSetup[index] = green;
                        break;
                    }
                }
            } else if (rules.rule.countExact == 0) {
                if (rules.rule.count == 0) {
                    for (int index = 0; index < wireCount; ++index) {
                        if (!changed[index] && wireSetup[index] != rules.rule.color) {
                            wireSetup[index] = rules.rule.color;
                            changed[index] = true;
                            break;
                        }
                    }
                } else {
                    for (int index = 0; index < wireCount; ++index) {
                        if (!changed[index] && wireSetup[index] == rules.rule.color) {
                            wireSetup[index] = green;
                            break;
                        }
                    }
                }
            }
        }

        rules = *rules.nextRule;
    }
}

// TODO should probably start with a lower probabilty and increase with higher
// rule indexes.
Rule determineSolvingRule(RuleSet rules, bool serialOdd)
{
    while (true) {
        if (random(100) < RULE_PROBABILITY) {
            Rule rule = rules.rule;
            while (!serialOdd) {
                if (rule.color == serial) {
                    return rules.nextRule->rule;
                }
                if (rule.additionalRule == nullptr) {
                    break;
                }
                rule = *rule.additionalRule;
            }
            return rules.rule;
        }
        if (rules.nextRule == nullptr) {
            break;
        }
        rules = *rules.nextRule;
    }
    return rules.rule;
}

int determineWireToCut(Rule solvingRule, Color wireSetup[])
{
    // Find the part of the rule that specifies the wire to cut
    while (solvingRule.cut < 0 && !solvingRule.cutColor) {
        solvingRule = *solvingRule.additionalRule;
    }

    // The wire to cut is specified by a simple index
    if (!solvingRule.cutColor) {
        return solvingRule.cut;
    }

    // The wire to cut is specified by 'cut the x-th wire of color y'
    int colorIndex = 0;
    if (solvingRule.cut >= 0) {
        for (int index = 0; index < 6; ++index) {
            if (wireSetup[index] == solvingRule.color) {
                if (colorIndex == solvingRule.cut) {
                    return index;
                }
                ++colorIndex;
            }
        }
    }

    // The wire to cut is specified by 'cut the x-th to last wire of color y'
    for (int index = 5; index >= 0; --index) {
        if (wireSetup[index] == solvingRule.color) {
            if (colorIndex == (-1 - solvingRule.cut)) {
                return index;
            }
            --colorIndex;
        }
    }

    // This should never be needed. If execution should reach this point, it means that the module couldn't handle a
    // specific rule and needs to be fixed.
    return 0;
}