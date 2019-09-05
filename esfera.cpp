#include "esfera.hpp"
#include <math.h>
#include <iostream>

#define CONSTROIORIGEM() this -> x = ponto -> getx(); \
  this -> y = ponto -> gety(); \
  this -> z = ponto -> getz(); \
  this -> origem = ponto

//double modulo(double d);

using namespace std;

Esfera::Esfera(Ponto* ponto,Material* material,double raio)
{
    CONSTROIORIGEM();
    this -> material = material;
    this -> raio = raio;
}

double Esfera::primeiraInterseccao(Reta* reta)
{
    double b, c; //Coeficientes da equacao quadratica das interseccoes
    double Delta; //Delta da equacao quadratica das interseccoes
    double Dx,Dy,Dz; //Coeficientes da direcao da reta parametrica
    double Px,Py,Pz; //Coordenadas da posicao inicial da reta parametrica
    double Cx,Cy,Cz; //Coordenadas do centro da esfera
    double C1,C2,C3; //Constantes usadas no calculo

    Dx = reta -> getDx();
    Dy = reta -> getDy();
    Dz = reta -> getDz();

    Px = reta -> getPx();
    Py = reta -> getPy();
    Pz = reta -> getPz();

    Cx = this -> x;
    Cy = this -> y;
    Cz = this -> z;

    C1 = Px - Cx;
    C2 = Py - Cy;
    C3 = Pz - Cz;

    //a = 1;
    b = 2*(C1*Dx + C2*Dy + C3*Dz);
    c = C1*C1 + C2*C2 + C3*C3 - raio*raio;

    Delta = b*b - 4*c;

    //return 100;

    if (Delta < 0)
    {
        //cout << Delta << endl;
        return 0;
    }
    else
        if (Delta == 0)
            return (-b/2.0);
        else
        {
            double Pos1, Pos2;
            Pos1 = (-b + sqrt(Delta))/2;
            Pos2 = (-b - sqrt(Delta))/2;

            if (Pos1 < Pos2) return Pos1;
            return Pos2;
        }
}

float Esfera::getx(){
    return x;
}

float Esfera::gety(){
    return y;
}

float Esfera::getz(){
    return z;
}

/* void Esfera::setx(float x)
{
	this -> x = x;
}

void Esfera::sety(float y)
{
	this -> y = y;
}

void Esfera::setz(float z)
{
	this -> z = z;
} */

void Esfera::setOrigem(Ponto* ponto)
{
    CONSTROIORIGEM();
}

Ponto* Esfera::getOrigem()
{
    return origem;
}

/* Material* Esfera::getMaterial(){
    return material;
} */

/* double modulo(double d)
{
    if (d >= 0) return d;
    return -d;
}*/

void Esfera::reescreve(Camera* c)
{
    origem -> reescreve(c);
    x = origem -> getx();
    y = origem -> gety();
    z = origem -> getz();
}

Vetor* Esfera::getNormal(Ponto* p)
{
    return UNITARIO(new Vetor(menos(p,origem)));
}

