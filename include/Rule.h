#ifndef RULE_H
#define RULE_H

#include <iostream>

#include <string>
#include <regex>
#include <algorithm>

#include <exception>

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
        bool isTwoPart() { return two_part; }

        string getAntecedenceInput1() { return antecedenceInput1; }
        string getAntecedenceCondition1() { return antecedenceCondition1; }
        SetOperation getOperation() { return operation; }
        string getAntecedenceInput2() { return antecedenceInput2; }
        string getAntecedenceCondition2() { return antecedenceCondition2; }
        string getConsequenceOutput() { return consequenceOutput; }
        string getConsequence() { return consequence; }

    private:
        string rule_full;
        bool two_part;

        string antecedenceInput1;
        string antecedenceCondition1;

        SetOperation operation;

        string antecedenceInput2;
        string antecedenceCondition2;

        string consequenceOutput;
        string consequence;
};

}

#endif // RULE_H
