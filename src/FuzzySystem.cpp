#include "FuzzySystem.h"

using namespace fsm;

FuzzySystem::FuzzySystem()
{
    //ctor
}

FuzzySystem::~FuzzySystem()
{
    //dtor
}

void FuzzySystem::applySettings(Settings s)
{
    //now apply settings.
    //do not changed settings until everything is properly initialized
    console_log("Applying rulebase...");
    Rulebase rb;
    try
    {
        rb = Rulebase(s.rulebaseName, s.rules);
    } catch (const exception& e)
    {
        console_write("Failed to apply rulebase.");
        console_write(e.what());
        console_write("Settings not applied.");
        return;
    }
    console_log("Rulebase applied.");

    console_log("Applying fuzzy input settings...");
    vector<FuzzyVariable> fuzzyvars;
    try
    {
        vector<fuzzy_pair> pairs = s.fuzzy_pairs;

        for (auto fuzzy_pair : pairs) {
            console_log("Building " + fuzzy_pair.first);
            vector<FuzzySet> sets;

            for (unsigned int i = 0; i < fuzzy_pair.second.size(); i++)
                sets.push_back(FuzzySet(fuzzy_pair.second[i]));
            fuzzyvars.push_back(FuzzyVariable(fuzzy_pair.first, sets));
        }

        if (fuzzyvars.size() < 3) throw runtime_error("System cannot have less than 2 inputs");
    } catch (const exception& e)
    {
        console_write("Error while applying crisp input settings.");
        console_write(e.what());
        console_write("Settings remain unchanged.");
        return;
    }
    console_log("Fuzzy settings applied.");

    k.fuzzyOut = fuzzyvars[fuzzyvars.size()-1]; //last fuzzyvariable is output
    fuzzyvars.pop_back();
    k.fuzzyIn = fuzzyvars;

    k.rb = rb;
    settings = s;
    console_write("Settings correctly applied.");

    init();
}

void FuzzySystem::init()
{
    fuzzyfier = Fuzzyfier();
    fuzzyfier.setCrispInput(&k.fuzzyIn);

    engine = InferenceEngine();
    engine.setRulebase(&k.rb);

    defuzzyfier = Defuzzyfier();
    defuzzyfier.setFuzzyOutput(&k.fuzzyOut);

    initialized = true;
}

void FuzzySystem::initSettingsFromFile(const char* path)
{
    Settings s;
    init_settings_from_file(s, path);
    applySettings(s);
}

void FuzzySystem::applyValues(map<string, float> vals)
{
    vector<float> result;

    for (auto f : k.fuzzyIn) {
        if (vals.find(f.getName()) != vals.end()) {
            result.push_back(vals[f.getName()]);
        } else {
            throw runtime_error("Error: value for " + f.getName() + " not defined.");
        }
    }

    currentValues = result;
}

void FuzzySystem::run(map<string, float> vals)
{
    try {
        applyValues(vals);
    } catch (const exception& e) {
        console_write("Cannot run fuzzy: Values incorrect.");
        console_write(e.what());
        return;
    }

    run();
}

void FuzzySystem::run(vector<float> vals)
{
    if (vals.size() != k.fuzzyIn.size()) throw runtime_error("Fuzzy system input must be same size as fuzzy variables in knowledge base.");
    currentValues = vals;
    run();
}

void FuzzySystem::run()
{
    if (!initialized)
        throw runtime_error("System uninitialized!");

    //fuzzyfy values
    console_log("");
    console_log("Fuzzyfying values");
    fuzzyfier.fuzzyfy(currentValues);
    vector<fuzzy_values> fuzzyfied = fuzzyfier.getResult();
    console_log("Values fuzzified");

    //infer
    console_log("Start Inference engine");
    fuzzy_engine_input engine_in; //fuzzyfied input to map
    for (unsigned int i = 0; i < fuzzyfied.size(); i++) {
        engine_in.push_back(pair<string, fuzzy_values>(k.fuzzyIn[i].getName(), fuzzyfied[i]));
    }
    engine.infer(engine_in);

    fuzzy_engine_output fuzzy_output = engine.getResult();

    //defuzzyfy
    defuzzyfier.defuzzyfy(fuzzy_output);
    currentResult = defuzzyfier.getResult();
}

void FuzzySystem::printResult()
{
    cout << k.fuzzyOut.getName() + " is " + to_string(currentResult) << endl;
}

