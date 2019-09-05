#include "objeto.hpp"
#include <stdlib.h>

Material* Objeto::getMaterial()
{
    return material;
}

Vetor* Objeto::getNormalDistorcida(Ponto* p)
{
    double rugosidade = material -> getRugosidade();

    int negx = (rand() % 2) - 1;
    int negy = (rand() % 2) - 1;
    int negz = (rand() % 2) - 1;

    Vetor* distorcao = VetorModuloX(new Vetor(rand() % 100,rand() % 100,rand() % 100),rugosidade);
    Vetor* normal = getNormal(p);
    Vetor* normaldistorcida = UNITARIO(Soma(*normal,*distorcao));

    if (ProdutoEscalar(*normal,*normaldistorcida) > 0) return normaldistorcida;
    return ProdutoPorEscalar(normaldistorcida,-1);
}


