#include "rule.h"

Rule wire3nr1 { red, -1, 0, 0, 1, false, nullptr };
Rule wire3nr2 { white, 2, -1, 0, 2, false, nullptr };
Rule wire3nr3 { blue, -1, 1, 2, -1, true, nullptr };
Rule wire3nr4 { unspecified, -1, -1, 0, 2, false, nullptr };

Rule wire4nr1pt2 { serial, 7, -1, 1, -1, false, nullptr };
Rule wire4nr1 { red, -1, 1, 2, -1, true, &wire4nr1pt2 };
Rule wire4nr2pt2 { red, -1, 0, 0, -1, false, nullptr };
Rule wire4nr2 { yellow, 3, -1, 0, 0, false, &wire4nr2pt2 };
Rule wire4nr3 { blue, -1, 1, 0, 0, false, nullptr };
Rule wire4nr4 { yellow, -1, 1, 2, 3, false, nullptr };
Rule wire4nr5 { unspecified, -1, -1, 0, 1, false, nullptr };

Rule wire5nr1pt2 { serial, 7, -1, 1, -1, false, nullptr };
Rule wire5nr1 { black, 4, -1, 0, 3, false, &wire5nr1pt2 };
Rule wire5nr2pt2 { yellow, -1, 1, 2, -1, false, nullptr };
Rule wire5nr2 { red, -1, 1, 0, 0, false, &wire5nr2pt2 };
Rule wire5nr3 { black, -1, 0, 0, 1, false, nullptr };
Rule wire5nr4 { unspecified, -1, -1, 0, 0, false, nullptr };

Rule wire6nr1pt2 { serial, 7, -1, 1, -1, false, nullptr };
Rule wire6nr1 { yellow, -1, 0, 0, 2, false, &wire6nr1pt2 };
Rule wire6nr2pt2 { white, -1, 1, 2, -1, false, nullptr };
Rule wire6nr2 { yellow, -1, 1, 0, 3, false, &wire6nr2pt2 };
Rule wire6nr3 { red, -1, 0, 0, 5, false, nullptr };
Rule wire6nr4 { unspecified, -1, -1, 0, 3, false, nullptr };

RuleSet wire3nr4Set { wire3nr4, nullptr };
RuleSet wire3nr3Set { wire3nr3, &wire3nr4Set };
RuleSet wire3nr2Set { wire3nr2, &wire3nr3Set };
RuleSet wire3nr1Set { wire3nr1, &wire3nr2Set };

RuleSet wire4nr5Set { wire4nr5, nullptr };
RuleSet wire4nr4Set { wire4nr4, &wire4nr5Set };
RuleSet wire4nr3Set { wire4nr3, &wire4nr4Set };
RuleSet wire4nr2Set { wire4nr2, &wire4nr3Set };
RuleSet wire4nr1Set { wire4nr1, &wire4nr2Set };

RuleSet wire5nr4Set { wire5nr4, nullptr };
RuleSet wire5nr3Set { wire5nr3, &wire5nr4Set };
RuleSet wire5nr2Set { wire5nr2, &wire5nr3Set };
RuleSet wire5nr1Set { wire5nr1, &wire5nr2Set };

RuleSet wire6nr4Set { wire6nr4, nullptr };
RuleSet wire6nr3Set { wire6nr3, &wire6nr4Set };
RuleSet wire6nr2Set { wire6nr2, &wire6nr3Set };
RuleSet wire6nr1Set { wire6nr1, &wire6nr2Set };

RuleSet RULE_BOOK[4] = { wire3nr1Set, wire4nr1Set, wire5nr1Set, wire6nr1Set };