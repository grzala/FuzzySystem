#include "FuzzySet.h"

using namespace fsm;

void FuzzySet::init(string name, float a, float b, float alpha, float beta)
{
    this->name = name;
    this->a = a;
    this->b = b;
    this->alpha = alpha;
    this->beta = beta;
}

FuzzySet::FuzzySet(string name, float a, float b, float alpha, float beta)
{
    init(name, a, b, alpha, beta);
}

FuzzySet::FuzzySet()
{
    init("", 0.f, 0.f, 0.f, 0.f);
}

FuzzySet::FuzzySet(string values)
{
    //intepret string into fuzzyset
    //tokenize by spaces
    vector<string> tokens;

    const char *str = values.c_str();
    char c = ' '; //split by spaces

    do
    {
        const char *begin = str;

        while(*str != c && *str)
            str++;

        tokens.push_back(string(begin, str));

    } while (0 != *str++);

    if (tokens.size() != 5) {
        throw invalid_argument("Fuzzy Set init string must look like this: name a b alpha beta");
    }

    init(tokens[0], stof(tokens[1]), stof(tokens[2]), stof(tokens[3]), stof(tokens[4]));
}

string FuzzySet::toString()
{
    stringstream str;
    str << "Fuzzy Set " << name << ": ";
    str << "a: " << a << " ";
    str << "b: " << b << " ";
    str << "alpha: " << alpha << " ";
    str << "beta: " << beta << endl;

    return str.str();
}


bool FuzzySet::operator <(const FuzzySet &other) const
{
    return this->b < other.a;
}

bool FuzzySet::operator >(const FuzzySet &other) const
{
    return this->a > other.b;
}


float FuzzySet::membership(float x)
{
    if (x > a - alpha && x < a)
    {
        return (x + (-a + alpha))/alpha;
    }
    else if (x >= a && x <= b)
    {
        return 1.0f;
    }
    else if (x > b && x < b + beta)
    {
        return ((b + beta) - x) / beta;
    }
    else
    {
        return 0.f;
    }
}

array<float, 2> FuzzySet::invert_membership(float y)
{
    array<float, 2> result;

    if (y > 1.f || y < 0.f)
        throw invalid_argument("y must be between 0 and 1");

    result[0] = (y*alpha) - (-a + alpha);
    result[1] = -(y*beta) + (b + beta);

    return result;
}
