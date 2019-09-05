#include "pontovetorcamera.hpp"
#include "material.hpp"
#include "reta.hpp"

#ifndef __OBJETO_HPP__

#define __OBJETO_HPP__


class Objeto
{
protected:
    Material* material;
    virtual Vetor* getNormal(Ponto*) = 0;
public:
    virtual void reescreve(Camera* c) = 0;
    virtual double primeiraInterseccao(Reta*) = 0;

    Vetor* getNormalDistorcida(Ponto*);

    Material* getMaterial();
};

#endif
