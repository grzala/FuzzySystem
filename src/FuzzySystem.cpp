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
    Rulebase* rb;
    try
    {
        rb = new Rulebase(s.rulebaseName, s.rules);
    } catch (const exception& e)
    {
        console_write("Failed to apply rulebase.");
        console_write(e.what());
        console_write("Settings not applied.");
        return;
    }
    console_log("Rulebase applied.");

    console_log("Applying fuzzy input settings...");
    array<FuzzyVariable, 3> fuzzyvars;
    try
    {
        string c1Name = s.fuzzy_in_1.first;
        vector<string> c1Sets = s.fuzzy_in_1.second;
        string c2Name = s.fuzzy_in_2.first;
        vector<string> c2Sets = s.fuzzy_in_2.second;
        string cOutName = s.fuzzy_out.first;
        vector<string> cOutSets = s.fuzzy_out.second;

        vector<FuzzySet> sets;

        for (unsigned int i = 0; i < c1Sets.size(); i++)
            sets.push_back(FuzzySet(c1Sets[i]));
        fuzzyvars[0] = FuzzyVariable(c1Name, sets);
        sets.clear();
        for (unsigned int i = 0; i < c2Sets.size(); i++)
            sets.push_back(FuzzySet(c2Sets[i]));
        fuzzyvars[1] = FuzzyVariable(c2Name, sets);
        sets.clear();
        for (unsigned int i = 0; i < cOutSets.size(); i++)
            sets.push_back(FuzzySet(cOutSets[i]));
        fuzzyvars[2] = FuzzyVariable(cOutName, sets);\

    } catch (const exception& e)
    {
        console_write("Error while applying crisp input settings.");
        console_write(e.what());
        console_write("Settings remain unchanged.");
        return;
    }
    console_log("Crisp settings applied.");

    console_log("Applying values...");
    array<pair<string, float>, 2> vals;
    try
    {
        array<string, 2> values {s.value1, s.value2};
        for (unsigned int i = 0; i < values.size(); i++)
        {
            //remove spaces
            string curval = values[i];
            curval.erase(std::remove(curval.begin(), curval.end(), ' '), curval.end());

            vector<string> tokens;
            const char *str = curval.c_str();
            char c = '='; //split by =
            do
            {
                const char *begin = str;
                while(*str != c && *str)
                str++;
                tokens.push_back(string(begin, str));
            } while (0 != *str++);

            if (tokens.size() != 2) {
                throw invalid_argument("Values did not follow convention: inputname = value");
            }
            pair<string, float> p(tokens[0], stof(tokens[1]));
            vals[i] = p;
        }
    } catch (const exception& e)
    {
        console_write("Error parsing values. Values must be written as: inputname = value");
        console_write(e.what());
        console_write("Settings were not applied.");
        return;
    }
    console_log("Values applied");

    //check if values can be applied
    FuzzyVariable temp1 = fuzzyIn1;
    FuzzyVariable temp2 = fuzzyIn2;

    fuzzyIn1 = fuzzyvars[0];
    fuzzyIn2 = fuzzyvars[1];
    try {
        applyValues(vals);
    } catch (const exception& e) {
        console_write("Values incorrect.");
        console_write(e.what());
        console_write("Settings remain unchanged");
        //revert changes
        fuzzyIn1 = temp1;
        fuzzyIn2 = temp2;
        return;
    }

    fuzzyOut = fuzzyvars[2];
    this->rb = *rb;
    settings = s;
    console_write("Settings correctly applied.");
}

void FuzzySystem::applyValues(pair<string, float> a, pair<string, float> b)
{
    float v1, v2;

    if (a.first == b.first)
        throw invalid_argument("Values cannot both refer to the same input (" + a.first + ")");

    if (fuzzyIn1.getName() == a.first)
        v1 = a.second;
    else if (fuzzyIn2.getName() == a.first)
        v2 = a.second;
    else
        throw invalid_argument("Input " + a.first + " not recognized");

    if (fuzzyIn1.getName() == b.first)
        v1 = b.second;
    else if (fuzzyIn2.getName() == b.first)
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
    fuzzyfier.setFuzzyInput(&fuzzyIn1, &fuzzyIn2);

    engine = InferenceEngine();
    engine.setRulebase(&rb);

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
        console_debug("Fuzzyfied value for: " + fuzzyIn1.getName());
        for (auto const& fuzzy_value : fs0) {
            console_debug(fuzzy_value.first + " " + to_string(fuzzy_value.second));
        }
        console_debug("");
        console_debug("Fuzzyfied value for: " + fuzzyIn2.getName());
        for (auto const& fuzzy_value : fs1) {
            console_debug(fuzzy_value.first + " " + to_string(fuzzy_value.second));
        }
        console_debug("");
    }

    //infer
    console_log("Start Inference engine");
    fuzzy_engine_input engine_in;
    engine_in[0] = pair<string, fuzzy_values>(fuzzyIn1.getName(), fuzzyfied[0]);
    engine_in[1] = pair<string, fuzzy_values>(fuzzyIn2.getName(), fuzzyfied[1]);
    engine.infer(engine_in);

    fuzzy_engine_output fuzzy_output = engine.getResult();

}

