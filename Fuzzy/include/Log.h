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
    BUILD = 3,
    VERBOSE = 2,
    NORMAL = 1,
    SILENT = 0,
};

void set_log_level(unsigned int i);

unsigned int get_log_level();

void console_debug(string s);
void console_log(string s);
void console_write(string s);

}

#endif // LOG_H
