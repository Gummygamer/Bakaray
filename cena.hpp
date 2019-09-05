#ifndef __CENA_HPP__

#define __CENA_HPP__

#include "objeto.hpp"
#include "luz.hpp"

class Cena{
private:
    Objeto** objetos;
    Luz** iluminacao;
    int numobjetos,numluzes;
public:
    Cena(Objeto**,Luz**,int numbolas,int numluzes);
    Objeto** getObjetos(void);
    int getNumObjetos(void);
    Luz** getLuzes(void);
    int getNumLuzes(void);

    void reescreve(Camera*);
};

#endif
