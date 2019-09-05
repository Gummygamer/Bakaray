#ifndef __RAYTRACING_HPP__

#define __RAYTRACING_HPP__

#include "cena.hpp"
#include "pontovetorcamera.hpp"
#include "resolucao.hpp"
#include <stdlib.h>

class RenderizadorBakaray{
private:
    Camera* camera;
    int tamx,tamy;
    Objeto** objetos;
    Luz** luzes;

    Cor** imagem;

    Ponto* pzero;

    float xpixel0,ypixel0;

    int numobjetos,numluzes;

    bool modoheuristico;

    void geraimagemheuristicamente();

    void geraimagem1raioporpixel();

    void geraimagem();

    void pintapixel(int i,int j,Cor);

    //Cor lancaraio(Reta*);

    Cor lancaraio(Reta*,int n);

    Cor lancaraio(int l,int c);

    Cor iluminacaolocal(Material* mat,Vetor* n,Vetor* v,Ponto* p);

public:
    RenderizadorBakaray(Camera*,Resolucao*,Cena*,bool);
    Cor** getImagem();
};

#endif
