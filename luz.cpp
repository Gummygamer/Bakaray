#include "luz.hpp"

Luz::Luz(Ponto* posicao,Cor* ambiente,Cor* difusa,Cor* especular,Atenuacao* a)
{
    this -> posicao = posicao;
    this -> ambiente = ambiente;
    this -> difusa = difusa;
    this -> especular = especular;
    this -> a = a;
}

Cor* Luz::getamb(){
    return ambiente;
}

Cor* Luz::getdif(){
    return difusa;
}

Cor* Luz::getesp(){
    return especular;
}

Ponto* Luz::getpos(){
    return posicao;
}

/*Ponto* Luz::setpos(Ponto* p)
{
	this -> posicao = p;
}*/

Atenuacao* Luz::getaten(){
    return a;
}

void Luz::reescreve(Camera* c)
{
    posicao -> reescreve(c);
}
