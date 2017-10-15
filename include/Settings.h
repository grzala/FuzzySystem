#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <array>

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

    private:
        static Settings *s_instance;
        bool initialized;
};


#endif // SETTINGS_H
