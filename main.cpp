#include <iostream>
#include <exception>

#include "Log.h"
#include "FuzzySystem.h"

//g++ min 4.9

using namespace fsm;

int main()
{
    set_log_level(log_level::BUILD);

    FuzzySystem fs;
    fs.initSettingsFromFile("example2.txt");

    try {
        fs.run();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }



    return 0;
}
