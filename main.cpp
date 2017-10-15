#include <iostream>
#include <stdexcept>

#include "Settings.h"

int main()
{
    Settings* s = Settings::instance();

    s->readSettingsFromFile("example.txt");



    return 0;
}
