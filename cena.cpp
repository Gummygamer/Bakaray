#include "cena.hpp"

Cena::Cena(Objeto** objetos,Luz** iluminacao,int numobjetos,int numluzes)
{
    this -> objetos = objetos;
    this -> iluminacao = iluminacao;
    this -> numobjetos = numobjetos;
    this -> numluzes = numluzes;
}

Objeto** Cena::getObjetos(void)
{
    return this -> objetos;
}

int Cena::getNumObjetos(void)
{
    return this -> numobjetos;
}

Luz** Cena::getLuzes(void)
{
    return this -> iluminacao;
}

int Cena::getNumLuzes(void)
{
    return this -> numluzes;
}

void Cena::reescreve(Camera* c)
{
    int cont;

    for (cont = numobjetos - 1; cont >=0; cont--) objetos[cont] -> reescreve(c);

    for (cont = numluzes - 1; cont >=0; cont--) iluminacao[cont] -> reescreve(c);
}

