#include <iostream>

#include "Log.h"
#include "FuzzySystem.h"

//g++ min 4.9

using namespace fsm;

int main()
{
    set_log_level(log_level::BUILD);

    FuzzySystem fs;
    fs.initSettingsFromFile("example.txt");



    return 0;
}
