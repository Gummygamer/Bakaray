#ifndef __ESFERA_HPP__

#define __ESFERA_HPP__

#include "objeto.hpp"

class Esfera: public Objeto
{
private:
    float x,y,z;
    Ponto* origem;
    double raio;
public:
    Esfera(Ponto*,Material*,double);

    double primeiraInterseccao(Reta*);

    void reescreve(Camera* c);

    Vetor* getNormal(Ponto*);

    float getx();
    float gety();
    float getz();

    Ponto* getOrigem();

    void setOrigem(Ponto*);

    //Material* getMaterial();
};

#endif
