#ifndef __RETA_HPP__

#define __RETA_HPP__

#include "pontovetorcamera.hpp"

class Reta{
private:
    Ponto* p;
    Vetor* d;
public:
    Reta(Ponto*,Vetor*);
    double getDx(void);
    double getDy(void);
    double getDz(void);
    Ponto* getP(void);
    Vetor* getD(void);
    float getPx(void);
    float getPy(void);
    float getPz(void);

    //double primeiraInterseccao(Reta* r);
};

#endif
