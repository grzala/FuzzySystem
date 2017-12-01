#include "Log.h"


static unsigned int level = 1;

void fsm::set_log_level(unsigned int i)
{
    level = i;
}

unsigned int fsm::get_log_level()
{
    return level;
}

void fsm::console_debug(string s)
{
    if (level >= 3) cout << s << endl;
}

void fsm::console_log(string s)
{
    if (level >= 2) cout << s << endl;
}

void fsm::console_write(string s)
{
    if (level >= 1) cout << s << endl;
}
