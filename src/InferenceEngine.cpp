#include "InferenceEngine.h"

using namespace fsm;

InferenceEngine::InferenceEngine()
{
    //ctor
}

InferenceEngine::~InferenceEngine()
{
    //dtor
}



void InferenceEngine::infer(fuzzy_engine_input in)
{
    vector<Rule> rules = rb->getRules();

    map<string, fuzzy_values> input_map;
    input_map[in[0].first] = in[0].second;
    input_map[in[1].first] = in[1].second;

    //infer
    vector<pair<string, float>> i_result;
    for (auto rule : rules)
    {
        string name1 = rule.getAntecedenceInput1();
        string consequenceName = rule.getConsequence();
        float val1 = input_map[name1][rule.getAntecedenceCondition1()];
        console_debug(name1 + ": " + to_string(val1));

        if (rule.isTwoPart())
        {
            string name2 = rule.getAntecedenceInput2();
            float val2 = input_map[name2][rule.getAntecedenceCondition2()];
            if (rule.getOperand() == OR) {
                console_debug("OR " + name2 + ": " + to_string(val2));
                i_result.push_back(pair<string, float>(consequenceName, max(val1, val2)));
            } else if (rule.getOperand() == AND) {
                console_debug("AND " + name2 + ": " + to_string(val2));
                i_result.push_back(pair<string, float>(consequenceName, min(val1, val2)));
            }
        } else
        {
            i_result.push_back(pair<string, float>(consequenceName, val1));
        }
        console_debug("");
    }
    console_debug("");

    //perform max if necessary
    fuzzy_engine_output result;
    for (unsigned int i = 0; i < i_result.size(); i++)
    {
        string name = i_result[i].first;
        float val = i_result[i].second;
        if (result.find(name) == result.end()) {
            result[name] = val;
        } else {
            result[name] = max(val, result[name]);
        }
    }

    console_log("Inference results:");
    for (const auto r : result) {
        console_debug(r.first + ": " + to_string(r.second));
    }

    this->result = result;
}
