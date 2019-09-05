#include "material.hpp"

#define BRILHOPADRAO 30

Material::Material(Cor* ambiente,Cor* difusa,Cor* especular,double brilho,double rugosidade)
{
    this -> ambiente = ambiente;
    this -> difusa = difusa;
    this -> especular = especular;
    this -> brilho = brilho * 128; // padrão para materiais: http://devernay.free.fr/cours/opengl/materials.html
    this -> rugosidade = rugosidade;
}
Material::Material(int red,int green,int blue)
{
    double dred = (double) red;
    double dgreen = (double) green;
    double dblue = (double) blue;

    Cor* padrao = new Cor(dred/255.0,dgreen/255.0,dblue/255.0);

    ambiente = padrao;
    difusa = padrao;
    especular = padrao;

    brilho = BRILHOPADRAO;

    rugosidade = 0;
}

Cor* Material::getamb(){
    return ambiente;
}

Cor* Material::getdif(){
    return difusa;
}

Cor* Material::getesp(){
    return especular;
}

double Material::getbrilho(){
    return brilho;
}

double Material::getRugosidade()
{
    return rugosidade;
}

