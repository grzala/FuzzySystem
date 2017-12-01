#include "Fuzzyfier.h"

using namespace fsm;

Fuzzyfier::Fuzzyfier()
{

}

void Fuzzyfier::fuzzyfy(vector<float> vals)
{
    fuzzyfier_output result;

    if (vals.size() != variables->size())
        throw new runtime_error("Fuzzyfier input size must be the same as fuzzy variables number");

    for (unsigned int i = 0; i < vals.size(); i++)
        result.push_back(pair<string, fuzzy_values>(variables->at(i).getName(), variables->at(i).calculateFuzzy(vals[i])));

    currentResult = result;
}


string Fuzzyfier::strfyResults()
{
    stringstream sstream;

    sstream << "Fuzzyfying results: " << endl;
    sstream << "--------------------" << endl;
    for (auto fuzzy_val : currentResult)
    {
        sstream << fuzzy_val.first << ": " << endl;
        for (fuzzy_values::iterator it = fuzzy_val.second.begin(); it != fuzzy_val.second.end(); ++it)
        {
            sstream << it->first << ": " << it->second << endl;
        }

        sstream << "------" << endl;
    }

    sstream << "--------------------" << endl;
    return sstream.str();
}
