#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <array>
#include <map>
#include <algorithm>

#include "Rulebase.h"
#include "Crisp.h"
#include "FuzzySet.h"


using namespace std;

class Settings
{
    public:
        Settings();
        ~Settings();

        static Settings *instance();

        void readSettingsFromFile(string path);
        void readSettingsFromString(string sets);

        bool isInitialized();

        Rulebase getRulebase() {return rulebase;}

        Crisp getCrispIn1() {return crispIn1;}
        Crisp getCrispIn2() {return crispIn2;}
        Crisp getCrispOut() {return crispOut;}

        map<string, float> getValues() {return values;}

    private:
        static Settings *s_instance;
        bool initialized;

        Rulebase rulebase;

        Crisp crispIn1;
        Crisp crispIn2;
        Crisp crispOut;

        map<string, float> values;

};


#endif // SETTINGS_H
