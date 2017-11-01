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
    string name;
    Rulebase rb;
    vector <FuzzyVariable> fuzzyIn;
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

        void applyValues(map<string, float> vals);

        void run();
        void run(map<string, float> vals);
        void run(vector<float> vals);
        bool run_from_stdin();

        float getResult() {return currentResult;}
        void printResult();

        vector<string> getFuzzyInNames() {
            vector<string> result;
            for (auto f : k.fuzzyIn) result.push_back(f.getName());
            return result;
        }
        string getFuzzyOutName() { return k.fuzzyOut.getName(); }
        vector<float> getCurrentValues() { return currentValues; }

        void checkKnowledgebaseIntegrity(KnowledgeBase k);

    private:
        bool initialized = false;

        //Knowledge Base/////////
        Settings settings;
        KnowledgeBase k;

        vector<float> currentValues;
        float currentResult = 0.f;
        //////////////////////////

        Fuzzyfier fuzzyfier;
        InferenceEngine engine;
        Defuzzyfier defuzzyfier;
};

}

#endif // FUZZYSYSTEM_H
