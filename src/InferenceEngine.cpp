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

    console_debug("Build input map");
    map<string, fuzzy_values> input_map;
    for (auto i : in) {
        input_map[i.first] = i.second;
    }


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
            console_debug(inputNames[0] + ": " + inputConditions[0] + ", " + consequence + ": " + to_string(val));
            i_result.push_back(pair<string, float>(consequence, val));
        } else
        {
            console_debug("Multipart antecedent");

            string debugstr;
            vector<float> values;
            for (unsigned int i = 0; i < inputNames.size(); i++) {
                values.push_back(input_map[inputNames[i]][inputConditions[i]]);
                debugstr.append(inputNames[i] + ": " + inputConditions[i] + ", ");
            }

            debugstr.append("possible values: ");
            for (float v : values)
                debugstr.append(to_string(v) + " ");

            float val;
            if (rule.getOperand() == OR) {
                debugstr.append("OR");
                val = *max_element(values.begin(), values.end());
            } else if (rule.getOperand() == AND) {
                debugstr.append("AND");
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

    this->result = result;
}

string InferenceEngine::strfyResults()
{
    stringstream sstream;

    sstream << rb->getName() << " min-max aggregate:" << endl;
    for (fuzzy_engine_output::iterator it = result.begin(); it != result.end(); ++it)
    {
        sstream << it->first << ": " << it->second << endl;
    }

    return sstream.str();
}
