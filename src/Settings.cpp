#include "Settings.h"

int read_from_file(string& content, const char* path)
{
    //open file
    ifstream inFile;
    inFile.open(path);

    //if file does not exists, report exception
    if (!inFile)
        return 0;

    //read file to string
    std::stringstream contentstream;
    contentstream << inFile.rdbuf();
    content = contentstream.str();

    //close file
    inFile.close();
    return 1;
}

bool isWhiteSpaceString(string s)
{
    return (s.find_first_not_of(" \t\n\v\f\r") == string::npos);
}

//find next empty or non empty line (ignore current line)
void nextLine(vector<string> lines, unsigned int& i, bool find_non_empty = false)
{
    do //move to next non empty line
    {
        i++;
        if (i == lines.size()) //end of vector reached
        {
            i--; //leave counter at last line to prevent out of bounds exception
            i--; //leave counter at last line to prevent out of bounds exception
            string err = "Runtime Exception: End of file reached, no ";
            err.append((find_non_empty) ? "non-empty" : "empty");
            err.append(" lines found");
            throw runtime_error(err);
        }
    } while (isWhiteSpaceString(lines[i]) == find_non_empty);
}

int fsm::init_settings_from_file(Settings& s, const char* path)
{
    //read content to string
    string content;
    if (!read_from_file(content, path))
    {
        console_write("File not found. Settings not changed.");
        return 0;
    }

    //interpret string line by line
    istringstream iss(content);
    vector<string> lines;

    for (string line; getline(iss, line);)
    {
        if (line.size() == 0 || (line.size() > 1 && line.at(0) != '#')) //ignore comments
            lines.push_back(line);
    }

    //interpret
    enum readState {
        RULEBASE,
        INPUT,
        VALUES,
        FINISHED,
    };

    readState state = RULEBASE;

    unsigned int i = 0;
    unsigned int input_no = 0;
    const unsigned int input_total = 3;

    console_log("Parsing file...");
    while (state != FINISHED) {

        switch(state)
        {
        case RULEBASE:
                console_log("Parsing rulebase...");
                //get first non-empty
                if (isWhiteSpaceString(lines[i])) nextLine(lines, i, true);
                s.rulebaseName = lines[i];
                console_log("Rulebase Name: " + s.rulebaseName);
                nextLine(lines, i, true); //go to rules

                console_log("Rules:");
                while (!isWhiteSpaceString(lines[i]))
                {
                    console_log(lines[i]);
                    s.rules.push_back(lines[i]);
                    i++;
                }
                console_log("");

                state = INPUT;
            break;

        case INPUT:
            {
                //get first non empty
                console_log("Parsing crisp...");
                nextLine(lines, i, true);
                string inputName(lines[i]);
                console_log("Crisp " + to_string(input_no) + ": " + inputName);

                nextLine(lines, i, true); //go to values
                vector<string> crispValues;
                while (!isWhiteSpaceString(lines[i]))
                {
                    console_log(lines[i]);
                    crispValues.push_back(lines[i]);
                    i++;
                }

                if (input_no == 0)
                    s.crisp_in_1 = crisp_pair(inputName, crispValues);
                else if (input_no == 1)
                    s.crisp_in_2 = crisp_pair(inputName, crispValues);
                else if (input_no == 2)
                    s.crisp_out = crisp_pair(inputName, crispValues);
                console_log("");

                input_no++;
                if (input_no == input_total)
                    state = VALUES;
            }
            break;

        case VALUES:
                console_log("Parsing values...");
                try { //if values are given in the end of file
                    nextLine(lines, i, true);
                    console_log("value 1: " + lines[i]);
                    s.value1 = lines[i];
                    i++;
                    console_log("value 2: " + lines[i]);
                    s.value2 = lines[i];
                } catch(std::exception& e) { //if no values are found, ask for manual input
                    cout << "No values were given or incorrectly defined. You can input them manually:" << endl;
                    string name1(s.crisp_in_1.first);
                    cout << name1 << " = ";
                    string in;
                    cin >> in;
                    in = name1.append(" = " + in);
                    s.value1 = in;

                    string name2(s.crisp_in_2.first);
                    cout << name2 << " = ";
                    cin >> in;
                    in = name2.append(" = " + in);
                    s.value2 = in;
                }

                state = FINISHED;

            break;

        case FINISHED:
            break;

        }
    }

    return 1;
}


/*



void Settings::readSettingsFromString(string sets)
{


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

    try
    {

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

    } catch (const std::exception& e)
    {
        cout << endl << "Error: Settings not initialized." << endl;
        cout << e.what();
        cout << "Is your input file properly structured?" << endl;

        return;
    }
    cout << endl << "Settings parsed. Applying settings..." << endl;

*/
