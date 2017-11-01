#include "Fuzzyfier.h"

using namespace fsm;

Fuzzyfier::Fuzzyfier()
{

}

void Fuzzyfier::fuzzyfy(vector<float> vals)
{
    vector<fuzzy_values> result;

    if (vals.size() != variables->size())
        throw new runtime_error("Fuzzyfier input size must be the same as fuzzy variables number");

    for (unsigned int i = 0; i < vals.size(); i++)
        result.push_back(variables->at(i).calculateFuzzy(vals[i]));

    currentResult = result;
}
