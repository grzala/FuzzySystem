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

    //std::vector<float> vals {17, 300};
    std::map<string, float> vals;
    //vals["temperature"] = 300;
    //vals["wind_speed"] = 17;
    //vals["humidity"] = 100;

    try {
        //fs.run(vals);
        while(fs.run_from_stdin())
            fs.printResult();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    /*
    try {
        Rule r1("Rule1: if temperature is high or temperature is bonkers or current is high or current is low or temperature is low then change_in_current is decrease");
        Rule r3("Rule1: If temperature is high then change_in_current is decrease");
        Rule r2("Rule1: If temperature is high or current is high or current is low then change_in_current is decrease");
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    */

    return 0;
}
