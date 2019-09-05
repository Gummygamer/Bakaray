#include "pontovetorcamera.hpp"
#include <iostream>

Ponto::Ponto(float x,float y,float z)
{
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

Ponto::Ponto(Vetor* v)
{
    this -> x = (float) v -> getx();
    this -> y = (float) v -> gety();
    this -> z = (float) v -> getz();
}

float Ponto::getx(void)
{
    return x;
}

float Ponto::gety(void)
{
    return y;
}

float Ponto::getz(void)
{
    return z;
}

void Ponto::setx(float x)
{
    this -> x = x;
}

void Ponto::sety(float y)
{
    this -> y = y;
}

void Ponto::setz(float z)
{
    this -> z = z;
}

Ponto* menos(Ponto* p1,Ponto* p2)
{
    return new Ponto(p1-> getx() - p2 -> getx(),p1 -> gety() - p2 -> gety(),p1-> getz() - p2 -> getz());
}

void Ponto::reescreve(Camera* c)
{
    Vetor* i = c -> geti();
    Vetor* j = c -> getj();
    Vetor* k = c -> getk();

    Ponto* poscam = c -> getPosicao();

    Ponto* ptrans = menos(this,poscam);


    float xtrans = ptrans -> getx();
    float ytrans = ptrans -> gety();
    float ztrans = ptrans -> getz();

    //cout << "(" << xtrans << "," << ytrans << "," << ztrans << ")" << endl;

    Vetor* trans = new Vetor(ptrans);

    // "rotação"

    this -> x = (float) ProdutoEscalar(*i,*trans);
    this -> y = (float) ProdutoEscalar(*j,*trans);
    this -> z = (float) ProdutoEscalar(*k,*trans);

    //cout << "(" << x << "," << y << "," << z << ")" << endl;

    //return new Ponto(x,y,z);
}



