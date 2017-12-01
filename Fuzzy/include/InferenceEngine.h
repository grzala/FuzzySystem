#ifndef INFERENCEENGINE_H
#define INFERENCEENGINE_H

#include <string>
#include <array>
#include <map>
#include <algorithm>

#include "Rulebase.h"
#include "FuzzyVariable.h"
#include "Log.h"

namespace fsm {

typedef vector<pair<string, fuzzy_values>> fuzzy_engine_input;
typedef map<string, float> fuzzy_engine_output;

class InferenceEngine
{
    public:
        InferenceEngine();
        virtual ~InferenceEngine();

        void setRulebase(Rulebase* a) {rb = a;}

        void infer(fuzzy_engine_input in);
        fuzzy_engine_output getResult() { return result; }

        string strfyResults();

    private:
        Rulebase* rb;
        fuzzy_engine_output result;
};

}

#endif // INFERENCEENGINE_H
