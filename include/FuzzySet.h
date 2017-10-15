#ifndef FUZZYSET_H
#define FUZZYSET_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <exception>

using namespace std;

class FuzzySet
{
    public:
        FuzzySet(string name, float a, float b, float alpha, float beta);
        FuzzySet(string values);
        FuzzySet();

        string Getname() {return name;}
        float Geta() { return a; }
        float Getb() { return b; }
        float Getalpha() { return alpha; }
        float Getbeta() { return beta; }

        string toString();

        bool operator <(const FuzzySet &other) const;
        bool operator >(const FuzzySet &other) const;

    private:
        void init(string name, float a, float b, float alpha, float beta);

        string name;
        float a;
        float b;
        float alpha;
        float beta;
};

#endif // FUZZYSET_H
