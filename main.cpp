#include <iostream>
#include <exception>

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

    //normally using typedef, stripped down for transparency
    string in_name1 = "temperature";
    map<string, float> fuzzy_in1;
    fuzzy_in1["low"] = 0.0;
    fuzzy_in1["medium"] = 0.33;
    fuzzy_in1["high"] = 0.33;
    pair<string, map<string, float>> fuzzy_pair1(in_name1, fuzzy_in1);

    string in_name2 = "current";
    map<string, float> fuzzy_in2;
    fuzzy_in2["low"] = 0.0;
    fuzzy_in2["medium"] = 0.3;
    fuzzy_in2["high"] = 0.7;
    pair<string, map<string, float>> fuzzy_pair2(in_name2, fuzzy_in2);

    vector<pair<string, map<string, float>>> inputs {fuzzy_pair1, fuzzy_pair1};

    engine.infer(inputs);

    std::cout << engine.strfyResults() << std::endl;
}

void run(string filename)
{
    FuzzySystem fs;
    fs.initSettingsFromFile(filename);

    //std::vector<float> vals {17, 300};
    std::map<string, float> vals;
    //vals["temperature"] = 300;
    //vals["wind_speed"] = 17;
    //vals["humidity"] = 100;

    try {
        //fs.run(vals);
        while(fs.run_from_stdin())
            fs.printResult();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
}

int main(int argc, char** argv)
{
    //set_log_level(log_level::BUILD);

    //test_fuzzyfier();
    test_inference();

    if (argc < 2) {
        std::cout << "No filename provided!" << endl;
        exit(1);
    }
    string filename = argv[1];
    //run(filename);

    return 0;
}

/*


    return 0;
*/
