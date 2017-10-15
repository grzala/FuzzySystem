#ifndef RULEBASE_H
#define RULEBASE_H

#include <string>
#include <vector>

#include "Rule.h"

using namespace std;

class Rulebase
{
    public:
        Rulebase();
        Rulebase(string name, vector<string> rules);
        virtual ~Rulebase();

        string Getname() { return name; }

    private:
        string name;
        vector<Rule> rules;
};

#endif // RULEBASE_H
