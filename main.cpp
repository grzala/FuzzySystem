#include <iostream>
#include <stdexcept>

#include "Settings.h"
#include "Fuzzyfier.h"

//g++ min 4.9
int main()
{
    Settings* s = Settings::instance();

    s->readSettingsFromFile("example.txt");

    std::cout << s->getRulebase().toString() << std::endl;


    Fuzzyfier *f = new Fuzzyfier(s->getCrispIn1(), s->getCrispIn2());
    f->setValues(s->getValues());

    f->fuzzify();



    delete f, s;

    return 0;
}
