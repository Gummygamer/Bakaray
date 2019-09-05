#include "triangulo.hpp"

Triangulo::Triangulo(Ponto* p0,Ponto* p1,Ponto* p2,Material* material)
{
    this -> material = material;

    this -> p0 = p0;
    this -> p1 = p1;
    this -> p2 = p2;
}

Vetor* Triangulo::getNormal(Ponto* p)
{
    return plano -> getNormal(p);
}

void Triangulo::reescreve(Camera* c)
{
    //plano -> reescreve(c);
    p0 -> reescreve(c);
    p1 -> reescreve(c);
    p2 -> reescreve(c);

    v0 = new Vetor(menos(p1,p0));
    v1 = new Vetor(menos(p2,p1));
    v2 = new Vetor(menos(p0,p2));

    Vetor* normal = UNITARIO(ProdutoVetorial(*v1,Vetor(menos(p0,p1))));

    plano = new Plano(normal,p0,material);
}

double Triangulo::primeiraInterseccao(Reta* r)
{
    double interplano = plano -> primeiraInterseccao(r);

    if (!interplano) return 0;

    Ponto* origem = r -> getP();

    Vetor* dir = r -> getD();

    Vetor vinter = *Soma(Vetor(origem),*ProdutoPorEscalar(dir,interplano));

    Ponto* pinter = &Ponto(&vinter);

    bool teste1 = ProdutoEscalar(*ProdutoVetorial(*v0,Vetor(menos(pinter,p0))),*getNormal(pinter)) >= 0;

    bool teste2 = ProdutoEscalar(*ProdutoVetorial(*v1,Vetor(menos(pinter,p1))),*getNormal(pinter)) >= 0;

    bool teste3 = ProdutoEscalar(*ProdutoVetorial(*v2,Vetor(menos(pinter,p2))),*getNormal(pinter)) >= 0;

    if (teste1 && teste2 && teste3) return interplano;

    return 0;
}

