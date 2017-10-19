#include "Rule.h"

using namespace fsm;

Rule::Rule()
{
    //ctor
}

Rule::Rule(string rule)
{
    this->rule_full = rule;
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
    two_part = false;
    if (regex_match(str, r))
        two_part = true;
    else
    {
        r = regex(".*? if .*? is .*? then .*?");
        if (!regex_match(str, r))
            throw invalid_argument("Invalid Rule: " + c_rule + "; Rule does not follow convention: if ____ is ____ and/or ___ is ___ then ___");
    }


    string operand;

    if (two_part)
    {
        //AND | OR
        str = rule;
        r = regex("(\\band\\b)"); //find all occurences of and
        ptrdiff_t const mm1(std::distance(std::sregex_iterator(str.begin(), str.end(), r), std::sregex_iterator()));
        r = regex("(\\bor\\b)"); // find all occurences of or
        ptrdiff_t const mm2(std::distance(std::sregex_iterator(str.begin(), str.end(), r), std::sregex_iterator()));

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
    }


    //antecendent1
    str = rule;
    if (two_part)
        r = regex("\\bif\\b(.*?)\\b" + operand + "\\b");
    else
        r = regex("\\bif\\b(.*?)\\bthen\\b");

    regex_search(str, m, r);
    if (m.size() < 2) throw invalid_argument("Invalid Rule: " + c_rule + "; Rule ill defined, no IF found.");

    string antecendent = m[1];

    str = antecendent;
    r = regex("([A-z]+) is ([A-z]+)");
    regex_search(str, m, r);
    if (m.size() < 3) throw invalid_argument("Invalid Rule: " + c_rule + "; Rule ill defined, something went wrong.");
    antecedenceInput1 = m[1];
    antecedenceCondition1 = m[2];

    //antecendent 2 is irrelevant if there is no AND/OR
    if (two_part)
    {
        //antecendent2
        str = rule;
        r = regex("\\b" + operand + "\\b(.*?)\\bthen\\b");
        regex_search(str, m, r);
        if (m.size() < 2) throw invalid_argument("Invalid Rule: " + c_rule + "; Rule ill defined, no IF found.");

        string antecedent2 = m[1];

        str = antecedent2;
        r = regex("([A-z]+) is ([A-z]+)");
        regex_search(str, m, r);
        if (m.size() < 3) throw invalid_argument("Invalid Rule: " + c_rule + "; Rule ill defined, something went wrong.");
        antecedenceInput2 = m[1];
        antecedenceCondition2 = m[2];
    }

    //consequent
    str = rule;
    r = regex("\\bthen\\b(.*?)$");
    regex_search(str, m, r);
    if (m.size() < 2) throw invalid_argument("Invalid Rule: " + c_rule + "; Rule ill defined, no THEN found.");

    string consequent = m[1];

    str = consequent;
    r = regex("([A-z]+) is ([A-z]+)");
    regex_search(str, m, r);
    if (m.size() < 3) {
        r = regex("([A-z]+) will be ([A-z]+)");
        regex_search(str, m, r);
    }

    if (m.size() < 3) throw invalid_argument("Invalid Rule: " + c_rule + "; Rule ill defined, something went wrong.");
    consequenceOutput = m[1];
    consequence = m[2];
}

Rule::~Rule()
{
    //dtor
}
