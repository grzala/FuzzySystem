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
        string antendenceInput1;
        string antendenceCondition1;

        SetOperation operation;

        string antendenceInput2;
        string antendenceCondition2;

        string consequenceOutput;
        string consequence;
};

#endif // RULE_H
