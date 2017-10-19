#ifndef FUZZYFIER_H
#define FUZZYFIER_H

#include <string>
#include <array>

#include <exception>

#include "Crisp.h"

typedef int fuzzyresults;

class Fuzzyfier
{
    public:
        Fuzzyfier(Crisp a, Crisp b);

        void setValues(array<pair<string, float>, 2> vals);
        void fuzzify();

    private:

        bool vals_initialized;

        Crisp cIn1;
        Crisp cIn2;

        pair <string, float> val1;
        pair <string, float> val2;


};

#endif // FUZZYFIER_H
