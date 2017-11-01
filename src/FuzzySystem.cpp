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

    KnowledgeBase k;
    k.name = s.rulebaseName;
    k.fuzzyOut = fuzzyvars[fuzzyvars.size()-1]; //last fuzzyvariable is output
    fuzzyvars.pop_back();
    k.fuzzyIn = fuzzyvars;

    k.rb = rb;

    try {
        checkKnowledgebaseIntegrity(k);
    } catch(exception& e)
    {
        console_write(e.what());
        console_write("Settings not applied.");
        return;
    }
    console_log("Knowledge base holds integrity.");

    this->k = k;
    settings = s;
    console_write("Settings applied.");

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
    console_log("Running for: " + k.name);
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

int find_fuzzy_by_name(vector<FuzzyVariable> fuzzys, string target) {
    for (unsigned int i = 0; i < fuzzys.size(); i++) {
        if (fuzzys[i].getName() == target)
            return i;
    }

    return -1;
}

void FuzzySystem::checkKnowledgebaseIntegrity(KnowledgeBase k)
{
    vector<FuzzyVariable> possible_antecedens = k.fuzzyIn;
    FuzzyVariable consequent = k.fuzzyOut;
    for (auto rule : k.rb.getRules()) {
        vector<string> antIn = rule.getAntecedenceInputs();
        vector<string> antCon = rule.getAntecedenceConditions();
        string conOut = rule.getConsequenceOutput();
        string con = rule.getConsequence();


        for (unsigned int i = 0; i < antIn.size(); i++) {
            int fuzzy_i = find_fuzzy_by_name(possible_antecedens, antIn[i]);
            if (fuzzy_i < 0) throw runtime_error("Antecedent " + antIn[i] + " has no valid corresponding fuzzy variable.");

            FuzzyVariable f = possible_antecedens[fuzzy_i];
            if (!f.hasSet(antCon[i])) throw runtime_error("Antecedent " + antIn[i] + " has no fuzzy set " + antCon[i]);
        }

        if (conOut != consequent.getName()) throw runtime_error("Consequent " + con + " does not correspond to fuzzy output name " + consequent.getName());
        if (!consequent.hasSet(con)) throw runtime_error("Consequent " + con + " has no fuzzy set " + con);
    }
}

bool FuzzySystem::run_from_stdin()
{
    cout << "Provide values for inputs. Type in 'q' at any time to exit." << endl;

    vector<string> inNames = getFuzzyInNames();
    string in;

    currentValues.clear();

    try {
        for (string inName : inNames)
        {
            cout << "Provide input for: " << inName << endl;

            cin >> in;
            if (in == "q") return false;

            currentValues.push_back(stof(in));
        }
    } catch (exception& e)
    {
        cout << "Error, wrong value provided. Could not convert " + in + " to float." << endl;
        return false;
    }

    cout << endl << endl;

    run();

    return true;
}

