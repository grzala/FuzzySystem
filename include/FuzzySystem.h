#ifndef FUZZYSYSTEM_H
#define FUZZYSYSTEM_H

#include <exception>

#include "Settings.h"
#include "Rulebase.h"
#include "FuzzyVariable.h"

#include "Fuzzyfier.h"

namespace fsm
{

class FuzzySystem
{
    public:
        FuzzySystem();
        virtual ~FuzzySystem();

        void applySettings(Settings s);
        void initSettingsFromFile(string s) {initSettingsFromFile(s.c_str());}
        void initSettingsFromFile(const char* path);

        void applyValues(array<pair<string, float>, 2> vals) {applyValues(vals[0], vals[1]);}
        void applyValues(pair<string, float> a, pair<string, float> b);

    private:
        Settings settings;

        Rulebase rb;
        FuzzyVariable fuzzyIn1;
        FuzzyVariable fuzzyIn2;
        FuzzyVariable fuzzyOut;

        float currentValue1;
        float currentValue2;

        Fuzzyfier fuzzyfier;
};

}

#endif // FUZZYSYSTEM_H
