#include "Crisp.h"

Crisp::~Crisp()
{

}

Crisp::Crisp(string name, vector<FuzzySet> fuzzysets)
{
    if (fuzzysets.size() != 3)
        throw invalid_argument("fuzzysets needs to contain exactly 3 sets");

    this->name = name;

    std::array<FuzzySet, 3> arr;
    std::copy_n(fuzzysets.begin(), 3, arr.begin());

    init(arr);
}

Crisp::Crisp(string name, array<FuzzySet, 3> fuzzysets)
{
    this->name = name;
    init(fuzzysets);
}

void Crisp::init(array<FuzzySet, 3> fuzzysets)
{
    sort(fuzzysets.begin(), fuzzysets.end());
    this->sets = fuzzysets;
}

string Crisp::toString()
{
    stringstream str;

    str << "Crisp input " << name << " consists of 3 fuzzy sets:" << endl;
    str << sets[0].toString() << sets[1].toString() << sets[2].toString();

    return str.str();
}