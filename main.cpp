#include <iostream>
#include <stdexcept>

#include "Log.h"
#include "Settings.h"

//g++ min 4.9

using namespace fsm;

int main()
{
    set_log_level(log_level::BUILD);

    Settings s;
    init_settings_from_file(s, "example.txt");



    return 0;
}
