#ifndef FUZZYSET_H
#define FUZZYSET_H

#include <iostream>
#include <string>
#include <sstream>

#include <array>
#include <vector>
#include <algorithm>
#include <iterator>
#include <exception>

using namespace std;

namespace fsm {

class FuzzySet
{
    public:
        FuzzySet(string name, float a, float b, float alpha, float beta);
        FuzzySet(string values);
        FuzzySet();

        string getName() {return name;}
        float getA() { return a; }
        float getB() { return b; }
        float getAlpha() { return alpha; }
        float getBeta() { return beta; }

        string toString();

        bool operator <(const FuzzySet &other) const;
        bool operator >(const FuzzySet &other) const;


        float membership(float x);
        array<float, 2> invert_membership(float y);

    private:
        void init(string name, float a, float b, float alpha, float beta);

        string name;
        float a;
        float b;
        float alpha;
        float beta;
};

}

#endif // FUZZYSET_H
