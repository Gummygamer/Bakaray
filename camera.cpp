#include "pontovetorcamera.hpp"


Camera::Camera(Ponto* localizacao,Vetor* orientacao,double distancia)
{
    this -> localizacao = localizacao;
    this -> orientacao = orientacao;
    this -> distancia = distancia;

    k = UNITARIO(orientacao);

    Vetor* up = new Vetor(0,1,0);

    i = UNITARIO(ProdutoVetorial(*k,*up));

    j = UNITARIO(ProdutoVetorial(*i,*k));
}

Camera::Camera(Ponto* localizacao,Vetor* orientacao,Vetor* up,double distancia)
{
    this -> localizacao = localizacao;
    this -> orientacao = orientacao;
    this -> distancia = distancia;

    k = UNITARIO(orientacao);

    up = UNITARIO(up);

    i = UNITARIO(ProdutoVetorial(*k,*up));

    j = UNITARIO(ProdutoVetorial(*i,*k));
}


Vetor* Camera::getDirecao(void)
{
    return orientacao;
}

Ponto* Camera::getPosicao(void)
{
    return localizacao;
}

double Camera::getDistancia(void)
{
    return distancia;
}

Vetor* Camera::geti()
{
    return i;
}

Vetor* Camera::getj()
{
    return j;
}

Vetor* Camera::getk()
{
    return k;
}



