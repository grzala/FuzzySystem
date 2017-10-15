#include <iostream>
#include <stdexcept>

#include "Settings.h"

//g++ min 4.9
int main()
{
    Settings* s = Settings::instance();

    s->readSettingsFromFile("example.txt");



    return 0;
}
