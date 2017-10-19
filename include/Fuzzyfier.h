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

        void setCrispInput(FuzzyVariable* a, FuzzyVariable* b);
        void fuzzyfy(float val1, float val2);
        array<fuzzy_values, 2> getResult() {return currentResult;}



    private:

        FuzzyVariable* fIn1;
        FuzzyVariable* fIn2;

        array<fuzzy_values, 2> currentResult;


};

}

#endif // FUZZYFIER_H
