#ifndef __PLANO_HPP__

#define __PLANO_HPP__

#include "objeto.hpp"

class Plano : public Objeto
{
private:
    Ponto* n1;
    Ponto* n2;
    Vetor* normal;
public:
    Plano(Vetor*,Ponto*,Material*);
    Plano(Ponto*,Ponto*,Material*);
    Vetor* getNormal(Ponto*);
    void reescreve(Camera* c);
    double primeiraInterseccao(Reta*);
};

#endif


