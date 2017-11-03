#include "Rulebase.h"

using namespace fsm;

Rulebase::Rulebase()
{
    //ctor
}

Rulebase::Rulebase(string name, vector<string> rules)
{
    this->name = name;

    for (unsigned int i = 0; i < rules.size(); i++)
    {
        this->rules.push_back(Rule(rules[i]));
    }
}

Rulebase::Rulebase(string name, vector<Rule> rules)
{
    this->name = name;

    this->rules = rules;
}

Rulebase::~Rulebase()
{
    //dtor
}
