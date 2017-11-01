#ifndef FUZZYFIER_H
#define FUZZYFIER_H

#include <string>
#include <array>

#include <exception>


#include "FuzzyVariable.h"

namespace fsm {

typedef vector<pair<string, fuzzy_values>> fuzzyfier_output;

class Fuzzyfier
{
    public:
        Fuzzyfier();

        void setFuzzyVariables(vector<FuzzyVariable>* variables) {this->variables = variables;}
        void fuzzyfy(vector<float> vals);
        fuzzyfier_output getResult() {return currentResult;}
        string strfyResults();

    private:
        vector<FuzzyVariable>* variables;

        fuzzyfier_output currentResult;

};

}

#endif // FUZZYFIER_H
