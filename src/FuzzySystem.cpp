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
            vector<FuzzySet> sets;

            for (unsigned int i = 0; i < c1Sets.size(); i++)
                sets.push_back(FuzzySet(c1Sets[i]));
            fuzzyvars.push_back(FuzzyVariable(c1Name, sets));
        }

    } catch (const exception& e)
    {
        console_write("Error while applying crisp input settings.");
        console_write(e.what());
        console_write("Settings remain unchanged.");
        return;
    }
    console_log("Crisp settings applied.");

    k.fuzzyIn1 = fuzzyvars[0];
    k.fuzzyIn2 = fuzzyvars[1];

    k.fuzzyOut = fuzzyvars[2];
    k.rb = rb;
    settings = s;
    console_write("Settings correctly applied.");
}

void FuzzySystem::applyValues(pair<string, float> a, pair<string, float> b)
{
    float v1, v2;

    if (a.first == b.first)
        throw invalid_argument("Values cannot both refer to the same input (" + a.first + ")");

    if (k.fuzzyIn1.getName() == a.first)
        v1 = a.second;
    else if (k.fuzzyIn2.getName() == a.first)
        v2 = a.second;
    else
        throw invalid_argument("Input " + a.first + " not recognized");

    if (k.fuzzyIn1.getName() == b.first)
        v1 = b.second;
    else if (k.fuzzyIn2.getName() == b.first)
        v2 = b.second;
    else
        throw invalid_argument("Input " + b.first + " not recognized");

    currentValue1 = v1;
    currentValue2 = v2;

    init();
}

void FuzzySystem::init()
{
    fuzzyfier = Fuzzyfier();
    fuzzyfier.setCrispInput(&k.fuzzyIn1, &k.fuzzyIn2);

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

void FuzzySystem::run(pair<string, float> a, pair<string, float> b)
{
    try {
        applyValues(a, b);
    } catch (const exception& e) {
        console_write("Cannot run fuzzy: Values incorrect.");
        console_write(e.what());
        return;
    }

    run();
}

void FuzzySystem::run(float a, float b)
{
    currentValue1 = a;
    currentValue2 = b;
    run();
}

void FuzzySystem::run()
{
    if (!initialized)
        throw runtime_error("System uninitialized!");

    //fuzzyfy values
    console_log("");
    console_log("Fuzzyfying values");
    fuzzyfier.fuzzyfy(currentValue1, currentValue2);
    array<fuzzy_values, 2> fuzzyfied = fuzzyfier.getResult();
    console_log("Values fuzzified");
    //print for debug
    if (get_log_level() == log_level::BUILD)
    {
        fuzzy_values fs0 = fuzzyfied[0]; fuzzy_values fs1 = fuzzyfied[1];
        console_debug("Fuzzyfied value for: " + k.fuzzyIn1.getName());
        for (auto const& fuzzy_value : fs0) {
            console_debug(fuzzy_value.first + " " + to_string(fuzzy_value.second));
        }
        console_debug("");
        console_debug("Fuzzyfied value for: " + k.fuzzyIn2.getName());
        for (auto const& fuzzy_value : fs1) {
            console_debug(fuzzy_value.first + " " + to_string(fuzzy_value.second));
        }
        console_debug("");
    }

    //infer
    console_log("Start Inference engine");
    fuzzy_engine_input engine_in;
    engine_in[0] = pair<string, fuzzy_values>(k.fuzzyIn1.getName(), fuzzyfied[0]);
    engine_in[1] = pair<string, fuzzy_values>(k.fuzzyIn2.getName(), fuzzyfied[1]);
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

