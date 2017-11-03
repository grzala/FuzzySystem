#include "Settings.h"

int read_from_file(string& content, const char* path)
{
    //open file
    ifstream inFile;
    inFile.open(path, ios_base::binary);

    //if file does not exists, report exception
    if (!inFile)
        return 0;

    //read file to string
    std::stringstream contentstream;
    contentstream << inFile.rdbuf();
    content = contentstream.str();
    transform(content.begin(), content.end(), content.begin(), ::tolower);

    //windows uses carriage returns - other OS do not
    #if !(_WIN64) && !(_WIN32)
    content.erase(remove(content.begin(), content.end(), '\r'), content.end());
    #endif

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
        if (i >= lines.size()) //end of vector reached
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
        if (!(line.size() > 1 && line.at(0) == '#')) //ignore comments
            lines.push_back(line);
    }

    cout << "NOW PRINTING ALLE LINER: " << endl;
    for (auto line : lines)
    {
        cout << line << endl;
    }
    cout << endl << endl;

    //interpret
    enum readState {
        RULEBASE,
        FUZZY_INPUT,
        FINISHED,
    };

    readState state = RULEBASE;

    unsigned int i = 0;

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

                state = FUZZY_INPUT;
            break;

        case FUZZY_INPUT:
            {
                //get first non empty
                console_log("Parsing crisp...");

                try { //do until end of file
                    nextLine(lines, i, true);
                    string inputName(lines[i]);
                    console_log("Crisp " + inputName);

                    nextLine(lines, i, true); //go to tuples
                    vector<string> fuzzyTuples;
                    while (i < lines.size() && !isWhiteSpaceString(lines[i]))
                    {
                        console_log(lines[i]);
                        fuzzyTuples.push_back(lines[i]);
                        i++;
                    }

                    s.fuzzy_pairs.push_back(fuzzy_pair(inputName, fuzzyTuples));
                } catch (std::exception& e) {
                    state = FINISHED;
                }

                console_log("");
            }
            break;

        case FINISHED:
            break;

        }
    }

    console_log("Settings loaded");

    return 1;
}

