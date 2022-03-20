#ifndef RULE
#define RULE

enum Color {
    red,
    blue,
    yellow,
    white,
    black,
    green,
    unspecified, // Used for rules that always apply
    serial // Used for rules like 'If the last digit of the serial number is odd' or
           // 'if the serial number contains a vowel'.
};

struct Rule {
    Rule()
        : color(unspecified)
        , position(-1)
        , count(-1)
        , countExact(0)
        , cut(-1)
        , cutColor(false)
        , additionalRule(nullptr)
    {
    }

    Rule(Color col, int p, int cou, int couEx, int ct, bool ctClr, Rule* add)
    {
        color = col;
        position = p;
        count = cou;
        countExact = couEx;
        cut = ct;
        cutColor = ctClr;
        additionalRule = add;
    }

    bool operator==(Rule& rhs)
    {
        return this->color == rhs.color && this->position == rhs.position && this->count == rhs.count
            && this->countExact == rhs.countExact && this->cut == rhs.cut && this->cutColor == rhs.cutColor
            && this->additionalRule == rhs.additionalRule;
    }

    bool operator!=(Rule& rhs)
    {
        return this->color != rhs.color || this->position != rhs.position || this->count != rhs.count
            || this->countExact != rhs.countExact || this->cut != rhs.cut || this->cutColor != rhs.cutColor
            || this->additionalRule != rhs.additionalRule;
    }

    // Specifies the color of the wires considered by this rule.
    // If the color is set to 'unspecified' the rules applies always and the wire
    // at 'cut' needs to be cut.
    Color color;

    // The position at which a wire of the specified color needs to be to fulfill
    // this rule. This property is exclusive with 'count'. If not used, the value
    // needs to be set to -1. The position is 0-based.
    //
    // Special case color=serial:
    // Specifies the position in the serial number that is needs to be considered.
    // Serial number has 8 digits.
    int position;

    // Specifies the amount of wires of the specified color need to be present to
    // fulfill this rule. Exclusive with 'position'. If not used, the value needs
    // to be set to -1.
    //
    // Special case color=serial:
    // Specifies the number of vowels that should be in the serial number.
    // TODO for now, this is not going to be used, since only the standard rules
    // will be implemented for now. In these only the last digit of the serial
    // number is checked for its evenness.
    int count;

    // To be used with 'count'.
    // Specifies how 'count' relates exactly to the actual amount of wires in the
    // specified color. If count is not used, the values of this property doesn't
    // matter, but 0 should be a good default.
    //
    // x is amount of wires of the specified color:
    //  0 : x == count
    //  1 : x >= count
    // -1 : x <= count
    //  2 : x > count
    // -2 : x < count
    //
    // Special case color=serial used with position instead of count:
    // Specifies the position in the serial number that is needs to be considered.
    //  0 : is even
    //  1 : is odd
    //  2 : is vowel
    // -2 : is consonant
    //
    // If color=serial is used with count, this prop works pretty much the same
    // as usual, just with the count of vowels instead of wires.
    //
    // TODO for now, the special case serial is barely used (and implemented),
    // since only the standard rules will be implemented for now. In these only the
    // last digit of the serial number is checked for its evenness.
    int countExact;

    // This specifies the index of the wire that needs to be cut if this rule
    // applies. If this is a composite rule, and this part of the Rule doesn't
    // specify the wire to be cut, set the value to -1. This property is 0-based.
    // If cutColor is 'true', a negative value specifies the 1-based index of
    // the wire that needs to be cut, starting by the last on of the specified
    // color. In that case it's still only the wires of the specified color,
    // that are considered when determining the index, just as with postive
    // values.
    int cut;

    // If true, the index specified by 'cut' only applies to wires of the
    // specified color. E.g. 'If there is more than one blue wire, cut the last
    // blue wire.' Otherwise false. If this is not the part of a composite rule
    // that specifies the wire to be cut, this needs to be false as well.
    bool cutColor;

    // A extern Rule may be composed of multiple rules that need to apply for the rule
    // to be fulfilled. These can be chained together via this prop. That last
    // extern Rule in the chain has this property set to NULL.
    // Only one of the rules will specify which wire to cut. If the wire to be
    // cut is color independent, it should be specified by the first rule.
    // If it's just a simple rule, this property is set to NULL as well.
    Rule* additionalRule;
};

struct RuleSet {

    RuleSet(Rule r, RuleSet* nr)
    {
        rule = r;
        nextRule = nr;
    }

    Rule rule;

    RuleSet* nextRule;
};

extern Rule wire3nr1;
extern Rule wire3nr2;
extern Rule wire3nr3;
extern Rule wire3nr4;

extern Rule wire4nr1pt2;
extern Rule wire4nr1;
extern Rule wire4nr2pt2;
extern Rule wire4nr2;
extern Rule wire4nr3;
extern Rule wire4nr4;
extern Rule wire4nr5;

extern Rule wire5nr1pt2;
extern Rule wire5nr1;
extern Rule wire5nr2pt2;
extern Rule wire5nr2;
extern Rule wire5nr3;
extern Rule wire5nr4;

extern Rule wire6nr1pt2;
extern Rule wire6nr1;
extern Rule wire6nr2pt2;
extern Rule wire6nr2;
extern Rule wire6nr3;
extern Rule wire6nr4;

extern RuleSet RULE_BOOK[4];

#endif