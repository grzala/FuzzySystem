#include <iostream>
#include <stdexcept>

#include "Settings.h"

int main()
{
    Settings* s = Settings::instance();

    try {
        s->readSettingsFromFile("example.txt");
    } catch (const std::exception& e) {
        cout << e.what();
    }



    return 0;
}
