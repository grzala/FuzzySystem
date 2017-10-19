#ifndef FUZZYVARIABLE_H
#define FUZZYVARIABLE_H

#include <string>
#include <sstream>
#include <array>
#include <map>
#include <vector>
#include <exception>

#include "FuzzySet.h"

namespace fsm {

typedef map<string, float> fuzzy_values;

class FuzzyVariable
{
    public:
        FuzzyVariable();
        FuzzyVariable(string name, vector<FuzzySet> fuzzysets);
        ~FuzzyVariable();

        string getName() { return name; }

        string toString();

        fuzzy_values calculateFuzzy(float val);


    protected:

    private:
        string name;
        vector <FuzzySet> sets;
};

}

#endif // FUZZYVARIABLE_H
