#include "atenuacao.hpp"

Atenuacao::Atenuacao(double a,double b,double c)
{
    this -> a = a;
    this -> b = b;
    this -> c = c;
}

double Atenuacao::geta(){
    return a;
}

double Atenuacao::getb(){
    return b;
}

double Atenuacao::getconst(){
    return c;
}

