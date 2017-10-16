#include "Fuzzyfier.h"

Fuzzyfier::Fuzzyfier(Crisp a, Crisp b)
{
    cIn1 = a; cIn2 = b;
    vals_initialized = false;
}


void Fuzzyfier::setValues(array<pair<string, float>, 2> vals)
{
    val1 = vals[0];
    val2 = vals[1];
    vals_initialized = true;
}

void Fuzzyfier::fuzzify()
{
    if (!vals_initialized)
        throw runtime_error("Fuzzyfier not properly initialized");


}
