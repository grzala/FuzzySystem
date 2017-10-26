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
        vector<string> inputNames = rule.getAntecedenceInputs();
        vector<string> inputConditions = rule.getAntecedenceConditions();

        string consequence = rule.getConsequence();

        if (inputNames.size() == 1) {
            console_debug("One part antecedent");
            float val = input_map[inputNames[0]][inputConditions[0]];
            console_debug(consequence + ": " + to_string(val));
            i_result.push_back(pair<string, float>(consequence, val));
        } else
        {
            console_debug("Multipart antecedent");
            vector<float> values;
            for (unsigned int i = 0; i < inputNames.size(); i++)
                values.push_back(input_map[inputNames[i]][inputConditions[i]]);

            string debugstr;
            float val;
            if (rule.getOperand() == OR) {
                debugstr = "OR";
                val = *max_element(values.begin(), values.end());
            } else if (rule.getOperand() == AND) {
                debugstr = "AND";
                val = *min_element(values.begin(), values.end());
            }
            debugstr.append(consequence + ": " + to_string(val));
            console_debug(debugstr);
            i_result.push_back(pair<string, float>(consequence, val));
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
