#ifndef FUZZYSYSTEM_H
#define FUZZYSYSTEM_H

#include <exception>

#include "Settings.h"
#include "Rulebase.h"
#include "FuzzyVariable.h"

#include "Fuzzyfier.h"
#include "InferenceEngine.h"
#include "Defuzzyfier.h"

//Fuzzy system contains the knowledge base

namespace fsm
{

struct KnowledgeBase {
    Rulebase rb;
    FuzzyVariable fuzzyIn1;
    FuzzyVariable fuzzyIn2;
    FuzzyVariable fuzzyOut;
};

class FuzzySystem
{
    public:
        FuzzySystem();
        virtual ~FuzzySystem();

        void applySettings(Settings s);
        void initSettingsFromFile(string s) {initSettingsFromFile(s.c_str());}
        void initSettingsFromFile(const char* path);
        void init();

        void applyValues(array<pair<string, float>, 2> vals) {applyValues(vals[0], vals[1]);}
        void applyValues(pair<string, float> a, pair<string, float> b);

        void run();
        void run(array<pair<string, float>, 2> vals) {run(vals[0], vals[1]);}
        void run(pair<string, float> a, pair<string, float> b);
        void run(float a, float b);

    private:
        bool initialized = false;

        //Knowledge Base/////////
        Settings settings;
        KnowledgeBase k;

        float currentValue1 = 0.f;
        float currentValue2 = 0.f;
        //////////////////////////

        Fuzzyfier fuzzyfier;
        InferenceEngine engine;
        Defuzzyfier defuzzyfier;
};

}

#endif // FUZZYSYSTEM_H
