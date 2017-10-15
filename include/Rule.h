#ifndef RULE_H
#define RULE_H

#include <iostream>

#include <string>
#include <regex>
#include <algorithm>

#include <exception>

using namespace std;

enum SetOperation {
    AND,
    OR,
};

class Rule
{
    public:
        Rule();
        Rule(string rule);
        virtual ~Rule();

        string getRuleFull() { return rule_full; }

    private:
        string rule_full;

        string antecedenceInput1;
        string antecedenceCondition1;

        SetOperation operation;

        string antecedenceInput2;
        string antecedenceCondition2;

        string consequenceOutput;
        string consequence;
};

#endif // RULE_H
