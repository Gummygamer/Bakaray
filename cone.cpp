#include "cone.hpp"

Cone::Cone(Ponto* p1,double h,Material* material)
{
    this -> p1 = p1;
    this -> h = h;

    p2 = new Ponto(p1 -> getx(),p1 -> gety() + h,p1 -> getz());

    this -> material = material;
}

void Cone::reescreve(Camera* c)
{
    p1 -> reescreve(c);
    p2 -> reescreve(c);
}

Vetor* Cone::getNormal(Ponto* p)
{
    Vetor baseponto = Vetor(menos(p,p1));

    Vetor pontotopo = Vetor(menos(p2,p));

    Vetor tangente2 = *ProdutoVetorial(baseponto,pontotopo);

    return UNITARIO(ProdutoVetorial(pontotopo,tangente2));
}

double Cone::primeiraInterseccao(Reta* r)
{
    double xd = r -> getDx();
    double yd = r -> getDy();
    double zd = r -> getDz();

    Ponto o = *(r -> getP());

    Ponto e = *menos(&o,p2);

    double xe = e.getx();
    double ye = e.gety();
    double ze = e.getz();

    double a = xd*xd + zd*zd - yd*yd;
    double b = xe*xd + ze*zd - ye*yd;
    b *= 2;

    double c = xe*xe + ze*ze - ye*ye;

    double delta = b*b - 4*a*c;

    if (delta < 0) return 0;

    if (delta < 0.001) return (-b)/(2*a);

    double raizdelta = sqrt(delta);

    double t1 = (-b - raizdelta)/(2*a);

    double t2 = (-b + raizdelta)/(2*a);

    double t;

    if (t1 < t2) t = t1;
    else t = t2;

    Ponto pinter = Ponto(Soma(Vetor(&o),*ProdutoPorEscalar(r -> getD(),t)));

    double y = pinter.gety();

    double y1 = p2 -> gety();

    double y0 = p1 -> gety();

    if (y > y1) return 0;

    if (y < y0) return 0;

    return t;
}


