#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <string>

using namespace std;

namespace fsm
{

//debug only in development
//log in verbose
//write always
enum log_level {
    BUILD = 2,
    VERBOSE = 1,
    NORMAL = 0,
    SILENT = -1,
};

void set_log_level(unsigned int i);

void console_debug(string s);
void console_log(string s);
void console_write(string s);

}

#endif // LOG_H
