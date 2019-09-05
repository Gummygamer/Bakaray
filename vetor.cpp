#include "pontovetorcamera.hpp"
#include <math.h>
#include <malloc.h>

Vetor::Vetor()
{
    x = y = z = 0;
}

Vetor::Vetor(double x, double y, double z)
{
    this -> x = x;
    this -> y = y;
    this -> z = z;
}

Vetor::Vetor(Ponto* p)
{
    this -> x = (double) p -> getx();
    this -> y = (double) p -> gety();
    this -> z = (double) p -> getz();
}

double Vetor::modulo(void)
{
    return sqrt(x*x + y*y + z*z);
}

double Vetor::getx(void)
{
    return x;
}

double Vetor::gety(void)
{
    return y;
}

double Vetor::getz(void)
{
    return z;
}

void Vetor::setx(double valor)
{
    x = valor;
}

void Vetor::sety(double valor)
{
    y = valor;
}

void Vetor::setz(double valor)
{
    z = valor;
}

double ProdutoEscalar(Vetor V1, Vetor V2)
{
    return (V1.getx())*(V2.getx()) + (V1.gety())*(V2.gety()) + (V1.getz())*(V2.getz());
}

Vetor* VetorModuloX(Vetor* VetorDirecao, double x)
{
    Vetor* temp;
    temp = new Vetor(0, 0, 0);
    double valor = x/(VetorDirecao -> modulo());
    temp -> setx(valor*(VetorDirecao -> getx()));
    temp -> sety(valor*(VetorDirecao -> gety()));
    temp -> setz(valor*(VetorDirecao -> getz()));
    return temp;
}

Vetor* ProdutoPorEscalar(Vetor* VetorDirecao, double x)
{
    /* VetorDirecao -> setx(VetorDirecao -> getx()*x);
    VetorDirecao -> sety(VetorDirecao -> gety()*x);
    VetorDirecao -> setz(VetorDirecao -> getz()*x); */

    return new Vetor(VetorDirecao -> getx()*x,VetorDirecao -> gety()*x,VetorDirecao -> getz()*x);
}


Vetor* ProdutoVetorial(Vetor V1, Vetor V2)
{
    Vetor* novo = new Vetor(0,0,0);
    novo -> setx(V1.gety()*V2.getz() - V1.getz()*V2.gety());
    novo -> sety(V1.getz()*V2.getx() - V1.getx()*V2.getz());
    novo -> setz(V1.getx()*V2.gety() - V1.gety()*V2.getx());
    return novo;
}

Vetor* Soma(Vetor V1, Vetor V2)
{
    Vetor* temp;
    temp = new Vetor((V1.getx()) + (V2.getx()),(V1.gety()) + (V2.gety()),(V1.getz()) + (V2.getz()));
    return temp;
}

double Angulo(Vetor* V1, Vetor* V2)
{
    return acos((ProdutoEscalar(*V1,*V2))/((V1 -> modulo())*(V2 -> modulo())));
}
