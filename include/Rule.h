#ifndef RULE_H
#define RULE_H

#include <iostream>

#include <string>
#include <regex>
#include <algorithm>

#include <exception>

#include "Log.h"

using namespace std;

namespace fsm {

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

        SetOperation getOperand() { return operand; }
        string getConsequenceOutput() { return consequenceOutput; }
        string getConsequence() { return consequence; }

        vector<string> getAntecedenceInputs() { return antecedenceInputs; }
        vector<string> getAntecedenceConditions() { return antecedenceConditions; }

    private:
        string rule_full;

        SetOperation operand;
        vector<string> antecedenceInputs;
        vector<string> antecedenceConditions;

        string consequenceOutput;
        string consequence;

        bool checkConvention(string rule);
        pair<string, int> countOperands(string rule);

        void parseAntecedents(string rule, string operand, int operand_no);
        void parseConsequent(string rule);
};

}

#endif // RULE_H
