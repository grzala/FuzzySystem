#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>

#include <string>
#include <vector>
#include <array>

#include <fstream>
#include <sstream>
#include <istream>

#include "Log.h"

using namespace std;

namespace fsm
{

typedef pair<string, vector<string>> fuzzy_pair;

struct Settings
{
    string rulebaseName;
    vector<string>rules;


    vector<fuzzy_pair> fuzzy_pairs;

    string value1;
    string value2;
};

extern int init_settings_from_file(Settings& s, const char* path);


}
#endif // SETTINGS_H
