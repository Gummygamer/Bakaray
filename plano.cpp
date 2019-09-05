#include "plano.hpp"

Plano::Plano(Vetor* n,Ponto* ponto,Material* material)
{
    normal = UNITARIO(n);

    n1 = ponto;

    Vetor* vn1 = new Vetor(n1);
    n2 = new Ponto(Soma(*vn1,*normal));

    this -> material = material;
}

Plano::Plano(Ponto* n1,Ponto* n2,Material* material)
{
    Ponto* pnormalbruta = menos(n2,n1);
    normal = UNITARIO(new Vetor(pnormalbruta));

    this -> n1 = n1;

    this -> n2 = n2;

    this -> material = material;
}

Vetor* Plano::getNormal(Ponto*)
{
    return normal;
}

void Plano::reescreve(Camera* c)
{
    n1 -> reescreve(c);
    n2 -> reescreve(c);

    Ponto* pn = menos(n2,n1);

    normal = UNITARIO(new Vetor(pn));
}

double Plano::primeiraInterseccao(Reta* r)
{
    Vetor* dirreta = r -> getD();
    Vetor orireta = Vetor(menos(r -> getP(),this->n1));

    double eqA = ProdutoEscalar(*dirreta,*normal);
    double eqB = ProdutoEscalar(orireta,*normal);

    if (fabs(eqA) < 0.001) return 0;

    double resultado = -eqB/eqA;

    if (resultado < 0.001) return 0;
    return resultado;
}


