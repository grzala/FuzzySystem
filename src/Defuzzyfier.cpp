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

float get_trapezoid_center(float a, float b, float c)
{
    float one = (2.f*a*c) + (a*a) + (c*b) + (a*b) + (b*b);
    float two = 3.f*(a+b);
    return one/two;
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
        float a = x_b - x_a; //top bar
        float b = (set->getB() + set->getBeta()) - (set->getA() - set->getAlpha()); //bottom bar
        float c = x_a-(set->getA() - set->getAlpha()); //distance from beggining of trapezoid to x_a

        console_debug("x_a: " + to_string(x_a) + "; x_b: " + to_string(x_b));
        console_debug("Calculating area |  a: " + to_string(a) + "; b:" + to_string(b) + "; c: " + to_string(c) + "; h: " + to_string(h) + ";");
        area = a+b;
        area = area/2;
        area = area*h;

        console_debug("Area of " + s.first + ": " + to_string(area));
        areas.push_back(area);

        float center = get_trapezoid_center(a, b, c); //get center relative to A
        center += set->getA() - set->getAlpha(); //calculate offset relative to global
        center = center - min_x; //offset to prevent negative (is this necessary?)
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

string Defuzzyfier::strfyResults()
{
    return string("Defuzzyfication result: " + to_string(result));
}
