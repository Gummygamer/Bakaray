#ifndef __PONTOVETORCAMERA_HPP__

#define __PONTOVETORCAMERA_HPP__

#define UNITARIO(x) VetorModuloX(x,1)

#include <math.h>

class Vetor;
class Camera;

class Ponto{
private:
    float x,y,z;

public:
    Ponto(float x,float y, float z);
    Ponto(Vetor*);

    float getx(void);
    float gety(void);
    float getz(void);
    void setx(float x);
    void sety(float y);
    void setz(float z);

    void reescreve(Camera* c);
};

Ponto* menos(Ponto* p1,Ponto* p2);

class Vetor{

private:
    double x,y,z;

public:
    Vetor();
    Vetor(double x, double y, double z);
    Vetor(Ponto*);
    double modulo(void);
    double getx(void);
    double gety(void);
    double getz(void);
    void setx(double valor);
    void sety(double valor);
    void setz(double valor);
};

class Camera{
private:
    Ponto* localizacao;
    Vetor* orientacao;
    double distancia;

    Vetor* i;
    Vetor* j;
    Vetor* k;

public:
    Camera(Ponto* loc,Vetor* dir,double dist);
    Camera(Ponto* loc,Vetor* dir,Vetor* up,double dist);
    Vetor* getDirecao(void);
    Ponto* getPosicao(void);
    double getDistancia(void);

    Vetor* geti();
    Vetor* getj();
    Vetor* getk();


};

double ProdutoEscalar(Vetor V1, Vetor V2);
Vetor* ProdutoVetorial(Vetor V1, Vetor V2);
Vetor* VetorModuloX(Vetor* VetorDirecao, double x);
Vetor* ProdutoPorEscalar(Vetor* VetorDirecao,double x);
Vetor* Soma(Vetor V1, Vetor V2);
double Angulo(Vetor* V1, Vetor* V2);


#endif
