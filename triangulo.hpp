#ifndef __TRIANGULO_HPP__

#define __TRIANGULO_HPP__

#include "plano.hpp"

class Triangulo : public Objeto
{
private:
    Ponto* p0;
    Ponto* p1;
    Ponto* p2;
    Vetor* v0;
    Vetor* v1;
    Vetor* v2;
    Plano* plano;
public:
    Triangulo(Ponto*,Ponto*,Ponto*,Material*);
    Vetor* getNormal(Ponto*);
    void reescreve(Camera* c);
    double primeiraInterseccao(Reta*);
};

#endif

