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

typedef pair<string, vector<string>> crisp_pair;

struct Settings
{
    string rulebaseName;
    vector<string>rules;


    crisp_pair crisp_in_1;
    crisp_pair crisp_in_2;
    crisp_pair crisp_out;

    string value1;
    string value2;
};

extern int init_settings_from_file(Settings& s, const char* path);


}
#endif // SETTINGS_H
