#include "Defuzzyfier.h"

using namespace fsm;

Defuzzyfier::Defuzzyfier()
{
    //ctor
}

Defuzzyfier::~Defuzzyfier()
{
    //dtor
}

void Defuzzyfier::defuzzyfy(map<string, float> in)
{
    vector<string> names;
    vector<float> areas;
    vector<float> centers;

    float min_x = fuzzy_output->getMinX();

    for (const auto s : in)
    {
        if (s.second <= 0.f) continue;
        FuzzySet* set = fuzzy_output->getSetByName(s.first);
        if (!set)
            throw runtime_error("Fuzzy variable " + fuzzy_output->getName() + " has no set named " + s.first);

        //trapezoid area
        float area;
        float h = s.second;
        array<float, 2> trapezoid_bounds = set->invert_membership(s.second);
        float x_a = trapezoid_bounds[0];
        float x_b = trapezoid_bounds[1];
        float a = x_b - x_a;
        float b = (set->getB() + set->getBeta()) - (set->getA() - set->getAlpha());

        console_debug("Calculating area |  a: " + to_string(a) + "; b:" + to_string(b) + "; h: " + to_string(h) + ";");
        area = a+b;
        area = area/2;
        area = area*h;

        console_debug("Area of " + s.first + ": " + to_string(area));
        areas.push_back(area);

        float center = ((set->getB() + set->getBeta()) + (set->getA() - set->getAlpha()))/2;
        center = center - min_x;
        console_debug("Center of " + s.first + ": " + to_string(center));
        centers.push_back(center);

        names.push_back(s.first);
    }

    //calculate crisp output
    float sum1 = 0.f;
    float sum2 = 0.f;

    for (unsigned int i = 0; i < names.size(); i++)
    {
        float a = areas[i] * centers[i];
        float b = areas[i];

        sum1 += a; sum2 += b;
    }
    console_debug("Sum1: " + to_string(sum1));
    console_debug("Sum2: " + to_string(sum2));

    result = sum1/sum2;
    result += min_x;
    console_debug("Result: " + to_string(result));
}
