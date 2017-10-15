#ifndef CRISP_H
#define CRISP_H

#include <string>

using namespace std;

class Crisp
{
    public:
        Crisp(string name, float a, float b, float alpha, float beta);
        Crisp(string name, string values);

        string Getnamename() {return name;}
        float Geta() { return a; }
        float Getb() { return b; }
        float Getalpha() { return alpha; }
        float Getbeta() { return beta; }

    protected:

    private:
        string name;
        float a;
        float b;
        float alpha;
        float beta;
};

#endif // CRISP_H
