#ifndef FUZZYFIER_H
#define FUZZYFIER_H

#include <string>
#include <array>

#include <exception>

#include "FuzzyVariable.h"

typedef int fuzzy_value;

class Fuzzyfier
{
    public:
        Fuzzyfier();

        void setCrispInput(FuzzyVariable* a, FuzzyVariable* b);


    private:


        FuzzyVariable* fIn1;
        FuzzyVariable* fIn2;


};

#endif // FUZZYFIER_H
