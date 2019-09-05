#ifndef __MATERIAL_HPP__

#define __MATERIAL_HPP__

#include "cor.hpp"

class Material{
private:
    Cor* ambiente;
    Cor* difusa;
    Cor* especular;
    double brilho;
    double rugosidade;
public:
    Material(Cor* ambiente,Cor* difusa,Cor* especular,double brilho,double rugosidade);
    Material(int red,int green,int blue);

    Cor* getamb();
    Cor* getdif();
    Cor* getesp();
    double getbrilho();
    double getRugosidade();
};

#endif
