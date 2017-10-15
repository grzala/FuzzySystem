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

    private:
        string antecedenceInput1;
        string antecedenceCondition1;

        SetOperation operation;

        string antecedenceInput2;
        string antecedenceCondition2;

        string consequenceOutput;
        string consequence;
};

#endif // RULE_H
