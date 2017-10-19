#include "Fuzzyfier.h"

using namespace fsm;

Fuzzyfier::Fuzzyfier()
{

}


void Fuzzyfier::setCrispInput(FuzzyVariable* a, FuzzyVariable* b)
{
    fIn1 = a;
    fIn2 = b;
}

void Fuzzyfier::fuzzyfy(float val1, float val2)
{
    array<fuzzy_values, 2> result;
    result[0] = fIn1->calculateFuzzy(val1);
    result[1] = fIn2->calculateFuzzy(val2);

    currentResult = result;
}
