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
    string content;

    try {
        //open file
        ifstream inFile;
        inFile.open(path);

        //if file does not exists, report exception
        if (!inFile)
            throw runtime_error("Settings file not found, settings remain unchanged");

        //read file to string
        std::stringstream contentstream;
        contentstream << inFile.rdbuf();
        content = contentstream.str();

        //close file
        inFile.close();

    } catch(const std::exception& e) {
        cout << "Settings not set, file " + path + " not found" << endl;
        return;
    }

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
        (*i)++;
        if (*i == lines.size()) //end of vector reached
        {
            (*i) --; //leave counter at last line to prevent out of bounds exception
            string err = "Runtime Exception: End of file reached, no ";
            err.append((find_non_empty) ? "non-empty" : "empty");
            err.append(" lines found\n");
            throw runtime_error(err);
        }
    }
}

void Settings::readSettingsFromString(string sets)
{
    //interpret string line by line
    istringstream iss(sets);
    vector<string> lines;

    for (string line; getline(iss, line);)
    {
        if (line.size() == 0 || (line.size() > 1 && line.at(0) != '#')) //ignore comments
            lines.push_back(line);
    }

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

    string rulebaseName;
    vector<string>rules;

    vector<string> inputNames;
    vector<vector<string>> inputs;

    vector<string> values;

    try {

    cout << "Parsing file..." << endl;
    while (state != FINISHED) {

        switch(state)
        {
        case RULEBASE:
                cout << "Parsing rulebase..." << endl;
                //get first non-empty
                nextLine(lines, &i, true);
                rulebaseName = lines[i];
                cout << "Rulebase Name: " << rulebaseName << endl;
                i++; nextLine(lines, &i, true); //go to rules
                //get rules
                nextLine(lines, &i, true);

                cout << "Rules:" << endl;
                while (!isWhiteSpaceString(lines[i]))
                {
                    cout << lines[i] << endl;
                    rules.push_back(lines[i]);
                    i++;
                }
                cout << endl;

                state = INPUT;
            break;

        case INPUT:
            {
                //get first non empty
                cout << "Parsing crisp..." << endl;
                nextLine(lines, &i, true);
                cout << "Crisp " << input_no << ": " << lines[i] << endl;
                inputNames.push_back(lines[i]);

                i++; nextLine(lines, &i, true); //go to values
                vector<string> crispValues;
                while (!isWhiteSpaceString(lines[i]))
                {
                    cout << lines[i] << endl;
                    crispValues.push_back(lines[i]);
                    i++;
                }
                inputs.push_back(crispValues);
                cout << endl;

                input_no++;
                if (input_no == input_total)
                    state = VALUES;
            }
            break;

        case VALUES:
                cout << "Parsing values:" << endl;
                try { //if values are given in the end of file
                    nextLine(lines, &i, true);
                    cout << "value 1: " << lines[i] << endl;
                    values.push_back(lines[i]);
                    i++;
                    cout << "value 2: " << lines[i] << endl;
                    values.push_back(lines[i]);
                } catch(std::exception& e) { //if no values are found, ask for manual input
                    cout << "No values were given or incorrectly defined. You can input them manually:" << endl;
                    cout << inputNames[0] << " = ";
                    string in;
                    cin >> in;
                    in = inputNames[0].append(" = " + in);
                    values.push_back(in);

                    cout << inputNames[1] << " = ";
                    cin >> in;
                    in = inputNames[1].append(" = " + in);
                    values.push_back(in);
                }

                state = FINISHED;

            break;

        case FINISHED:
            break;

        }

    }

    } catch (const std::exception& e) {
        cout << endl << "Error: Settings not initialized." << endl;
        cout << e.what();
        cout << "Is your input file properly structured?" << endl;

        return;
    }

    cout << "Settings parsed. Applying settings..." << endl;

    cout << "Applying crisp input settings..." << endl;
    for (unsigned int i = 0; i < inputNames.size(); i++)
    {
        array<FuzzySet, 3> sets;
        for (unsigned int j = 0; j < inputs[i].size(); j++)
        {
            FuzzySet f(inputs[i][j]);
            sets[j] = f;
        }
        Crisp c(inputNames[i], sets);
        cout << c.toString() << endl;
    }
}
