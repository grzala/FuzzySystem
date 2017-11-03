#ifndef DEFUZZYFIER_H
#define DEFUZZYFIER_H

#include <exception>

#include "Log.h"
#include "FuzzyVariable.h"

namespace fsm {

class Defuzzyfier
{
    public:
        Defuzzyfier();
        virtual ~Defuzzyfier();

        void setFuzzyOutput(FuzzyVariable* out) { this->fuzzy_output = out; }
        void defuzzyfy(map<string, float> in);

        float getResult() { return result; }
        string strfyResults();

    private:

        FuzzyVariable* fuzzy_output;
        float result;
};

}

#endif // DEFUZZYFIER_H
