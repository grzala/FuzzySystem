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
        bool isTwoPart() { return false; }

        string getAntecedenceInput1() { return antecedenceInput1; }
        string getAntecedenceCondition1() { return antecedenceCondition1; }
        SetOperation getOperand() { return operand; }
        string getAntecedenceInput2() { return antecedenceInput2; }
        string getAntecedenceCondition2() { return antecedenceCondition2; }
        string getConsequenceOutput() { return consequenceOutput; }
        string getConsequence() { return consequence; }

        vector<string> getAntecedenceInputs() { return antecedenceInputs; }
        vector<string> getAntecedenceConditions() { return antecedenceConditions; }

    private:
        string rule_full;

        string antecedenceInput1;
        string antecedenceCondition1;

        SetOperation operand;

        string antecedenceInput2;
        string antecedenceCondition2;

        string consequenceOutput;
        string consequence;

        vector<string> antecedenceInputs;
        vector<string> antecedenceConditions;

        bool checkConvention(string rule);
        pair<string, int> countOperands(string rule);

        void parseAntecedents(string rule, string operand, int operand_no);
        void parseConsequent(string rule);
};

}

#endif // RULE_H
