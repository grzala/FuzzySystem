#include "Rule.h"

Rule::Rule()
{
    //ctor
}

Rule::Rule(string rule)
{
    cout << "TESTING REGEX" << endl << endl;

    string c_rule = rule;
    transform(rule.begin(), rule.end(), rule.begin(), ::tolower);
    //rule.erase(std::remove(rule.begin(), rule.end(), ' '), rule.end());
    string str;
    regex r;
    smatch m;
    smatch m2;

    //check rule convention
    str = rule;
    r = regex(".*? if .*? is .*? (and|or) .*? is .*? then .*?");
    if (!regex_match(str, r))
        throw invalid_argument("Rule does not follow convention: if ____ is ____ and/or ___ is ___ then ___");


    //AND | OR
    str = rule;
    r = regex("(\\band\\b)"); //find all occurences of and
    ptrdiff_t const mm1(std::distance(std::sregex_iterator(str.begin(), str.end(), r), std::sregex_iterator()));
    r = regex("(\\bor\\b)"); // find all occurences of or
    ptrdiff_t const mm2(std::distance(std::sregex_iterator(str.begin(), str.end(), r), std::sregex_iterator()));

    string operand;
    if (mm1 > 0 && mm2 > 0) {
        throw invalid_argument("Invalid Rule: " + c_rule + "; Cannot use both AND and OR operands in one rule.");
    } else if (mm1 > 1) {
        throw invalid_argument("Invalid Rule: " + c_rule + "; Multiple AND detected.");
    } else if (mm2 > 1) {
        throw invalid_argument("Invalid Rule: " + c_rule + "; Multiple OR detected.");
    } else if (mm1 == 1 && mm2 == 0) {
        operand = "and";
        operation = AND;
    } else if (mm1 == 0 && mm2 == 1) {
        operand = "or";
        operation = OR;
    } else {
        throw invalid_argument("Invalid Rule: " + c_rule + "; Neither AND or OR detected.");
    }


    //antecendent
    str = rule;
    r = regex("\\bif\\b(.*?)\\b" + operand + "\\b");
    regex_search(str, m, r);
    if (m.size() < 2)
        throw invalid_argument("Rule ill defined, no IF found.");

    string antecendent = m[1];
    cout << antecendent << endl;

    cout << endl;
}

Rule::~Rule()
{
    //dtor
}
