#ifndef CRISP_H
#define CRISP_H

#include <string>
#include <sstream>
#include <array>
#include <map>
#include <vector>
#include <exception>

#include "FuzzySet.h"

class Crisp
{
    public:
        Crisp();
        Crisp(string name, array<FuzzySet, 3> fuzzysets);
        Crisp(string name, vector<FuzzySet> fuzzysets);
        ~Crisp();

        string Getname() { return name; }

        string toString();

        array<pair<string, float>, 3> calculateFuzzy(float val);


    protected:

    private:
        string name;
        array <FuzzySet, 3> sets;

        void init(array<FuzzySet, 3> fuzzysets);
};

#endif // CRISP_H
