#ifndef FUZZYSYSTEM_H
#define FUZZYSYSTEM_H

#include "Settings.h"

namespace fsm
{

class FuzzySystem
{
    public:
        FuzzySystem();
        virtual ~FuzzySystem();

    private:
        Settings settings;
};

}

#endif // FUZZYSYSTEM_H
