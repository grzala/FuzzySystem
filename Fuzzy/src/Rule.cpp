#include "Rule.h"

using namespace fsm;

Rule::Rule()
{
    //ctor
}

Rule::Rule(string rule)
{
    console_debug("Parsing rule: " + rule);
    this->rule_full = rule;
    string c_rule = rule;
    transform(rule.begin(), rule.end(), rule.begin(), ::tolower);
    //rule.erase(std:remove(rule.begin(), rule.end(), ' '), rule.end());
    string str;
    regex r;
    smatch m;
    smatch m2;

    //check rule convention
    console_debug("Checking rule convention...");
    if (!checkConvention(rule))
        throw invalid_argument("Invalid Rule: " + c_rule + "; Rule does not follow convention: if ____ is ____ and/or ___ is ___ then ___");


    //AND | OR
    console_debug("Counting and/or");
    pair<string, int> op = countOperands(rule);
    string operand = op.first;
    int operand_no = op.second;
    if (operand == "and")
        this->operand = AND;
    else if (operand == "or")
        this->operand = OR;

    //antecendents
    console_debug("Parse antecedents");
    parseAntecedents(rule, operand, operand_no);

    //consequent
    console_debug("Parse consequent");
    parseConsequent(rule);

    console_debug("Rule completed\n");
}

Rule::~Rule()
{
    //dtor
}

bool Rule::checkConvention(string rule)
{
    regex r;
    r = regex("(.*?)if .*? is .*? then .*?");
    return regex_match(rule, r);
}

pair<string, int> Rule::countOperands(string rule)
{
    regex r;
    string operand;
    int operand_no = 0;

    r = regex("(\\band\\b)"); //find all occurences of and
    ptrdiff_t const no_and(std::distance(std::sregex_iterator(rule.begin(), rule.end(), r), std::sregex_iterator()));
    r = regex("(\\bor\\b)"); // find all occurences of or
    ptrdiff_t const no_or(std::distance(std::sregex_iterator(rule.begin(), rule.end(), r), std::sregex_iterator()));

    if (no_and > 0 && no_or > 0) {
        throw invalid_argument("Invalid Rule: " + rule + "; Cannot use both AND and OR operands in one rule.");
    } else if (no_and > 0) {
        operand = "and";
        operand_no = (int)no_and;
    } else if (no_or > 0) {
        operand = "or";
        operand_no = (int)no_or;
    }

    return pair<string, int>(operand, operand_no);
}

void Rule::parseAntecedents(string rule, string operand, int operand_no)
{
    regex r;
    vector<string> antecedents;
    if (operand_no == 0)
    {
        smatch m;
        r = regex("if\\b.*?\\bthen\\b");
        regex_search(rule, m, r);
        if (m.size() < 1) throw invalid_argument("Invalid Rule: " + rule + "; Rule ill defined, no IF THEN found.");
        antecedents.push_back(m[0]);
    }
    else
    {
        r = regex("(if\\b.*?(?=\\b"+operand+"\\b))|(\\b"+operand+"\\b.*?(?=\\b"+operand+"\\b))|(\\b"+operand+"\\b.*?\\bthen\\b)");

        const auto begin_iterator = std::sregex_iterator( rule.cbegin(), rule.cend(), r );
        const auto end_iterator = std::sregex_iterator();

        for (std::sregex_iterator i = begin_iterator; i != end_iterator; ++i) {
            std::smatch match = *i;
            std::string match_str = match.str();
            antecedents.push_back(match_str);
        }

        if (antecedents.size() == 0) throw invalid_argument("Invalid Rule: " + rule + "; Rule ill defined");
    }

    smatch m;
    for (auto antecedent: antecedents)
    {
        r = regex("([A-z]+) is ([A-z]+)");
        regex_search(antecedent, m, r);
        if (m.size() < 3) throw invalid_argument("Invalid Rule: " + rule + "; Rule ill defined, something went wrong here: " + antecedent);
        antecedenceInputs.push_back(m[1]);
        antecedenceConditions.push_back(m[2]);
    }
}

void Rule::parseConsequent(string rule)
{
    regex r; smatch m;
    r = regex("\\bthen\\b(.*?)$");
    regex_search(rule, m, r);
    if (m.size() < 2) throw invalid_argument("Invalid Rule: " + rule + "; Rule ill defined, no THEN found.");

    string consequent = m[1];
    r = regex("([A-z]+) is ([A-z]+)");
    regex_search(consequent, m, r);
    if (m.size() < 3) {
        r = regex("([A-z]+) will be ([A-z]+)");
        regex_search(consequent, m, r);
    }

    if (m.size() < 3) throw invalid_argument("Invalid Rule: " + rule + "; Rule ill defined, something went wrong here: " + consequent);
    consequenceOutput = m[1];
    consequence = m[2];
}
