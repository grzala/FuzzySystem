#ifndef FUZZYFIER_H
#define FUZZYFIER_H

#include <string>
#include <array>

#include <exception>


#include "FuzzyVariable.h"

namespace fsm {

class Fuzzyfier
{
    public:
        Fuzzyfier();


        void setCrispInput(vector<FuzzyVariable>* variables) {this->variables = variables;}
        void fuzzyfy(vector<float> vals);
        vector<fuzzy_values> getResult() {return currentResult;}



    private:
        vector<FuzzyVariable>* variables;

        vector<fuzzy_values> currentResult;


};

}

#endif // FUZZYFIER_H
