#include <iostream>
#include <exception>
#include <cstring>

#include "Log.h"
#include "FuzzySystem.h"

//g++ min 4.9

using namespace fsm;

void test_fuzzyfier()
{
    //fuzzy variable temperature, 3 fuzzy sets
    FuzzySet s1("low 0 100 0 100");
    FuzzySet s2("medium 200 200 150 150");
    FuzzySet s3("high 400 450 150 0");
    FuzzyVariable temperature("temperature", std::vector<FuzzySet> {s1, s2, s3});

    //fuzzy variable current, 3 fuzzy sets
    FuzzySet s4("low 0 0 0 10");
    FuzzySet s5("medium 10 10 10 10");
    FuzzySet s6("high 20 20 10 0");
    FuzzyVariable current("current", std::vector<FuzzySet> {s4, s5, s6});

    //initialize fuzzyfier
    vector<FuzzyVariable> fuzzy_variables {temperature, current};
    Fuzzyfier fuzzyfier;
    fuzzyfier.setFuzzyVariables(&fuzzy_variables);

    //fuzzyfy for input
    vector<vector<float>> inputs_list {
        vector<float> {300, 17},
        vector<float> {200, 10},
        vector<float> {100, 2},
        vector<float> {350, 5},
        vector<float> {-100, 500}
    };

    for (auto inputs : inputs_list)
    {
        cout << "Fuzzyfy for inputs: ";
        for (auto i : inputs) cout << i << " ";
        cout << endl;

        fuzzyfier.fuzzyfy(inputs);
        //print output
        std::cout << fuzzyfier.strfyResults() << std::endl;
    }
}

void test_inference()
{
    //define rules
    Rule r1("if temperature is high or current is high then change_in_current is decrease");
    Rule r2("if temperature is medium then change_in_current is no_change");
    Rule r3("if temperature is low and current is high then change_in_current is no_change");
    Rule r4("if temperature is low and current is low then change_in_current is increase)");

    //construct rulebase
    Rulebase rulebase(string("thermostat"), vector<Rule> {r1, r2, r3, r4});

    //initialize inference angine
    InferenceEngine engine;
    engine.setRulebase(&rulebase);

    const unsigned int ins_no = 3;
    float ins1[ins_no][3] = {{0.0, 0.33, 0.33}, {0.2, 0.5, 0.0}, {0.7, 0.2, 0.0}};
    float ins2[ins_no][3] = {{0.0, 0.3, 0.7}, {0.0, 1.0, 0.0}, {0.8, 0.1, 0.0}};

    //normally using typedef, stripped down for transparency
    for (unsigned int i = 0; i < ins_no; ++i)
    {
        string in_name1 = "temperature";
        map<string, float> fuzzy_in1;
        fuzzy_in1["low"] = ins1[i][0];
        fuzzy_in1["medium"] = ins1[i][1];
        fuzzy_in1["high"] = ins1[i][2];
        pair<string, map<string, float>> fuzzy_pair1(in_name1, fuzzy_in1);
        std::cout << "Running for input: " << std::endl;
        std::cout << fuzzy_pair1.first << ": {low: " << fuzzy_pair1.second["low"] << ", medium: " << fuzzy_pair1.second["medium"] << ", high: " << fuzzy_pair1.second["high"] << "}\n";

        string in_name2 = "current";
        map<string, float> fuzzy_in2;
        fuzzy_in2["low"] = ins2[i][0];
        fuzzy_in2["medium"] = ins2[i][1];
        fuzzy_in2["high"] = ins2[i][2];
        pair<string, map<string, float>> fuzzy_pair2(in_name2, fuzzy_in2);
        std::cout << fuzzy_pair2.first << ": {low: " << fuzzy_pair2.second["low"] << ", medium: " << fuzzy_pair2.second["medium"] << ", high: " << fuzzy_pair2.second["high"] << "}\n";

        vector<pair<string, map<string, float>>> inputs {fuzzy_pair1, fuzzy_pair2};

        std::cout << "Start Inference engine...\n";
        engine.infer(inputs);

        std::cout << "Output:\n" << engine.strfyResults() << std::endl;
        std::cout << std::endl;
    }
}

void test_defuzzyfier()
{
    //fuzzy variable temperature, 3 fuzzy sets
    FuzzySet out1("decrease -50 -50 50 50");
    FuzzySet out2("no_change 0 0 50 50");
    FuzzySet out3("increase 50 50 50 50");
    FuzzyVariable out("change_in_current", std::vector<FuzzySet> {out1, out2, out3});

    Defuzzyfier deffuzyfier;
    deffuzyfier.setFuzzyOutput(&out);

    const int in_no = 3;
    float in_vals[in_no][3] = {{0.7, 0.33, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.2, 0.3}};

    for (int i = 0; i < in_no; i++)
    {
        std::cout << "Deffuzying values: " << std::endl;
        std::cout << "decrease: " << in_vals[i][0] << "; " << "no_change: " << in_vals[i][1] << "; " << "increase: " << in_vals[i][2] << ";" << std::endl;

        map<string, float> in;
        in["decrease"] = in_vals[i][0];
        in["no_change"] = in_vals[i][1];
        in["increase"] = in_vals[i][2];

        std::cout << "Defuzzyfying..." << std::endl;

        deffuzyfier.defuzzyfy(in);

        std::cout << deffuzyfier.strfyResults() << std::endl << std::endl;
    }
}

typedef struct {
    const char* command_line = "-c";
} Args;
static Args args;

int main(int argc, char** argv)
{
    #ifdef BUILD_FOR_DEVELOPMENT
        set_log_level(log_level::BUILD);
    #endif

    if (argc < 2) {
        std::cout << "No filename provided!" << endl;
        exit(1);
    }

    //parse parameters
    string filename; bool filename_initialized = false;
    vector<float> inputs;
    bool run_from_cmd = false;
    for (int i = 1; i < argc; ++i)
    {
        if ((strcmp(args.command_line, argv[i]) == 0))
        {
            run_from_cmd = true;
        } else if (!filename_initialized)
        {
            filename = argv[i];
            filename_initialized = true;
        } else
        {
            inputs.push_back(stof(argv[i]));
        }
    }


    FuzzySystem fs;

    try {
        fs.initSettingsFromFile(filename);
    } catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    //run
    if (run_from_cmd)
    {
        try {
            while(fs.run_from_stdin())
                std::cout << fs.strfyResults() << std::endl << std::endl;
        } catch (const exception& e) {
            cout << e.what() << endl;
        }
    } else
    {
        if (inputs.size() != fs.inputCount()) {
            std::cout << "Wrong number of inputs provided" << endl;
            exit(1);
        }

        fs.run(inputs);
        std::cout << fs.strfyResults() << std::endl;
    }


    return 0;
}
