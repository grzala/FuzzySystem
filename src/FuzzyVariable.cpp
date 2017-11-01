#include "FuzzyVariable.h"

using namespace fsm;

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

    str << "FuzzyVariable " << name << " consists of fuzzy sets:" << endl;
    for (FuzzySet s : sets) {
        str << s.toString();
    }

    return str.str();
}


fuzzy_values FuzzyVariable::calculateFuzzy(float val)
{
    map<string, float> result;
    for (unsigned int i = 0; i < sets.size(); i++)
    {
        FuzzySet s = sets[i];
        result[s.getName()] = s.membership(val);
    }
    return result;
}

FuzzySet* FuzzyVariable::getSetByName(string name)
{
    for (unsigned int i = 0; i < sets.size(); i++)
    {
        if (sets[i].getName() == name) return &sets[i];
    }
    return nullptr;
}

bool FuzzyVariable::hasSet(string name)
{
    for (auto s : sets)
    {
        if (s.getName() == name) return true;
    }

    return false;
}

float FuzzyVariable::getMinX()
{
    float minX = std::numeric_limits<float>::max();

    for (auto s : sets) {
        float x = s.getA() - s.getAlpha();
        if (x < minX) minX = x;
    }

    return minX;
}
