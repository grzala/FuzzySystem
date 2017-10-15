#include "Settings.h"

//Settings is a singleton available anywhere in the program

Settings* Settings::s_instance = nullptr;

Settings::Settings()
{
    initialized = false;
}

Settings::~Settings() {

}

bool Settings::isInitialized()
{
    return initialized;
}

Settings* Settings::instance()
{
    if (!s_instance)
        s_instance = new Settings();
    return s_instance;
}

//init settings from file
void Settings::readSettingsFromFile(string path)
{
    //open file
    ifstream inFile;
    inFile.open(path);

    //if file does not exists, report exception
    if (!inFile)
        throw runtime_error("Settings file not found, settings remain unchanged");

    //read file to string
    std::stringstream contentstream;
    contentstream << inFile.rdbuf();
    string content = contentstream.str();

    //close file
    inFile.close();

    //set settings
    readSettingsFromString(content);
}

void Settings::readSettingsFromString(string sets)
{
    //interpret string line by line
    istringstream iss(sets);
    vector<string> lines;

    for (string line; getline(iss, line);)
        lines.push_back(line);

    enum readState {
        RULEBASE,
        INPUT,
        VALUES,
    };

    readState state = RULEBASE;
    bool lastCharacterWhite = false;

    unsigned int i = 0;

    while (i < lines.size()) {
        switch(state)
        {
        case RULEBASE:
            //if(line.find_first_not_of(' ') == string::npos)
            cout << "RULEBASE NAME: " << lines[i] << endl;
            i++; //next line
            while (lines[i].find_first_not_of(' ') == string::npos) //move to next non empty line
                i++;

            //get rules
            while (lines[i].find_first_not_of(' ') == string::npos) //move to next non empty line

            state = INPUT;
            break;
        }

        i++;
    }
}
