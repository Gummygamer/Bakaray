#ifndef __LUZ_HPP__

#define __LUZ_HPP__

#include "pontovetorcamera.hpp"
#include "cor.hpp"
#include "atenuacao.hpp"

class Luz{
private:
    Ponto* posicao;
    Cor* ambiente;
    Cor* difusa;
    Cor* especular;
    Atenuacao* a;
public:
    Luz(Ponto* posicao,Cor* ambiente,Cor* difusa,Cor* especular,Atenuacao* a);
    Cor* getamb();
    Cor* getdif();
    Cor* getesp();
    Ponto* getpos();

    void setpos(Ponto*);

    void reescreve(Camera* c);

    Atenuacao* getaten();
};

#endif
