#ifndef __CONE_HPP__

#define __CONE_HPP__

#include "objeto.hpp"

class Cone : public Objeto
{
private:
    Ponto* p1;
    Ponto* p2;
    double h;
public:
    Cone(Ponto*,double,Material*);
    Vetor* getNormal(Ponto*);
    void reescreve(Camera* c);
    double primeiraInterseccao(Reta*);
};

#endif
