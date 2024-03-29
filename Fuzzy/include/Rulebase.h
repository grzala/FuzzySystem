#ifndef RULEBASE_H
#define RULEBASE_H

#include <string>
#include <sstream>
#include <vector>

#include "Rule.h"

using namespace std;

namespace fsm {

class Rulebase
{
    public:
        Rulebase();
        Rulebase(string name, vector<string> rules);
        Rulebase(string name, vector<Rule>rules);
        virtual ~Rulebase();

        string getName() { return name; }
        string toString() {
            stringstream ss;
            ss << "Rulebase " << name << endl;
            for (unsigned int i = 0; i < rules.size(); i++)
            {
                ss << rules[i].getRuleFull() << endl;
            }
            return ss.str();
        }

        vector<Rule> getRules() {return rules;}

    private:
        string name;
        vector<Rule> rules;
};

}

#endif // RULEBASE_H
