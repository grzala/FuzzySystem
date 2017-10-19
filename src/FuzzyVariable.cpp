#include "FuzzyVariable.h"

FuzzyVariable::FuzzyVariable()
{
    name = "";
}

FuzzyVariable::~FuzzyVariable()
{

}

FuzzyVariable::FuzzyVariable(string name, vector<FuzzySet> fuzzysets)
{
    this->name = name;

    sort(fuzzysets.begin(), fuzzysets.end());
    this->sets = fuzzysets;
}

string FuzzyVariable::toString()
{
    stringstream str;

    str << "FuzzyVariable " << name << " consists of 3 fuzzy sets:" << endl;
    str << sets[0].toString() << sets[1].toString() << sets[2].toString();

    return str.str();
}


array<pair<string, float>, 3> FuzzyVariable::calculateFuzzy(float val)
{
    array<pair<string, float>, 3> result;
    for (unsigned int i = 0; i < sets.size(); i++)
    {
        FuzzySet s = sets[i];
        result[i] = pair<string, float>(s.Getname(), s.membership(val));
    }
    return result;
}
