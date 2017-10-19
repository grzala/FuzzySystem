#include "Log.h"


static unsigned int level = 0;

void fsm::set_log_level(unsigned int i)
{
    level = i;
}

void fsm::console_debug(string s)
{
    if (level >= 2) cout << s << endl;
}

void fsm::console_log(string s)
{
    if (level >= 1) cout << s << endl;
}

void fsm::console_write(string s)
{
    if (level >= 0) cout << s << endl;
}