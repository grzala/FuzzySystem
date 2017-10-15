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

bool isWhiteSpaceString(string s)
{
    return (s.find_first_not_of(" \t\n\v\f\r") == string::npos);
}

//find next empty or non empty line (omit current line)
void nextLine(vector<string> lines, unsigned int* i, bool find_non_empty = false)
{
    while (isWhiteSpaceString(lines[*i]) == find_non_empty) //move to next non empty line
    {
        if (*i == lines.size())
            return; //EOS
        (*i)++;
    }
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
        FINISHED,
    };

    readState state = RULEBASE;

    int input_no = 0;
    const int input_total = 3;
    unsigned int i = 0;

    while (state != FINISHED) {

        switch(state)
        {
        case RULEBASE:
                //get first non-empty
                nextLine(lines, &i, true);
                cout << "RULEBASE NAME: " << lines[i] << endl;
                i++; nextLine(lines, &i, true); //go to rules
                //get rules
                nextLine(lines, &i, true);
                while (!isWhiteSpaceString(lines[i]))
                {
                    cout << "Rule X: " << lines[i] << endl;
                    i++;
                }

                state = INPUT;
            break;

        case INPUT:
                //get first non empty
                nextLine(lines, &i, true);
                cout << "Input " << input_no << ": " << lines[i] << endl;
                i++; nextLine(lines, &i, true); //go to values

                while (!isWhiteSpaceString(lines[i]))
                {
                    cout << "Rule X: " << lines[i] << endl;
                    i++;
                }

                input_no++;
                if (input_no == input_total)
                    state = VALUES;
            break;

        case VALUES:
                nextLine(lines, &i, true);
                cout << "VAL1: " << lines[i] << endl;
                i++;
                cout << "VAL2: " << lines[i] << endl;

                state = FINISHED;

            break;

        case FINISHED:
            break;

        }

    }
}
