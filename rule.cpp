#include "rule.h"

Rule wire3nr1 { red, -1, 0, 0, 1, false, nullptr };
Rule wire3nr2 { white, 2, -1, 0, 2, false, nullptr };
Rule wire3nr3 { blue, -1, 1, 2, -1, true, nullptr };
Rule wire3nr4 { unspecified, -1, -1, 0, 2, false, nullptr };

Rule wire4nr1pt2 { serial, 5, -1, 1, -1, false, nullptr };
Rule wire4nr1 { red, -1, 1, 2, -1, true, &wire4nr1pt2 };
Rule wire4nr2pt2 { red, -1, 0, 0, -1, false, nullptr };
Rule wire4nr2 { yellow, 3, -1, 0, 0, false, &wire4nr2pt2 };
Rule wire4nr3 { blue, -1, 1, 0, 0, false, nullptr };
Rule wire4nr4 { yellow, -1, 1, 2, 3, false, nullptr };
Rule wire4nr5 { unspecified, -1, -1, 0, 1, false, nullptr };

Rule wire5nr1pt2 { serial, 5, -1, 1, -1, false, nullptr };
Rule wire5nr1 { black, 4, -1, 0, 3, false, &wire5nr1pt2 };
Rule wire5nr2pt2 { yellow, -1, 1, 2, -1, false, nullptr };
Rule wire5nr2 { red, -1, 1, 0, 0, false, &wire5nr2pt2 };
Rule wire5nr3 { black, -1, 0, 0, 1, false, nullptr };
Rule wire5nr4 { unspecified, -1, -1, 0, 0, false, nullptr };

Rule wire6nr1pt2 { serial, 5, -1, 1, -1, false, nullptr };
Rule wire6nr1 { yellow, -1, 0, 0, 2, false, &wire6nr1pt2 };
Rule wire6nr2pt2 { white, -1, 1, 2, -1, false, nullptr };
Rule wire6nr2 { yellow, -1, 1, 0, 3, false, &wire6nr2pt2 };
Rule wire6nr3 { red, -1, 0, 0, 5, false, nullptr };
Rule wire6nr4 { unspecified, -1, -1, 0, 3, false, nullptr };

RuleSet RULE_BOOK[4]
    = { RuleSet(wire3nr1, new RuleSet(wire3nr2, new RuleSet(wire3nr3, new RuleSet(wire3nr4, nullptr)))),
          RuleSet(wire4nr1,
              new RuleSet(wire4nr2, new RuleSet(wire4nr3, new RuleSet(wire4nr4, new RuleSet(wire4nr5, nullptr))))),
          RuleSet(wire5nr1, new RuleSet(wire5nr2, new RuleSet(wire5nr3, new RuleSet(wire5nr4, nullptr)))),
          RuleSet(wire6nr1, new RuleSet(wire6nr2, new RuleSet(wire6nr3, new RuleSet(wire6nr4, nullptr)))) };