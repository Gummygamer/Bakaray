#include "reta.hpp"

Reta::Reta(Ponto* p,Vetor* d)
{
    this -> p = p;
    this -> d = UNITARIO(d);
}

double Reta::getDx(void)
{
    return d -> getx();
}

double Reta::getDy(void)
{
    return d -> gety();
}

double Reta::getDz(void)
{
    return d -> getz();
}

Ponto* Reta::getP(void)
{
    return p;
}

Vetor* Reta::getD(void)
{
    return d;
}

float Reta::getPx(void)
{
    return p -> getx();
}

float Reta::getPy(void)
{
    return p -> gety();
}

float Reta::getPz(void)
{
    return p -> getz();
}

