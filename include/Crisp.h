#ifndef CRISP_H
#define CRISP_H

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <exception>

#include "FuzzySet.h"

class Crisp
{
    public:
        Crisp(string name, array<FuzzySet, 3> fuzzysets);
        Crisp(string name, vector<FuzzySet> fuzzysets);
        ~Crisp();

        string Getname() { return name; }

        string toString();

    protected:

    private:
        string name;
        array <FuzzySet, 3> sets;

        void init(array<FuzzySet, 3> fuzzysets);
};

#endif // CRISP_H
