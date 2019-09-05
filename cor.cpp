#include "cor.hpp"

#define SOMACOMP(x) x + c.x

#define SUBCOMP(x) x - c.x

double valabs(double d)
{
    if (d < 0) return -d;
    return d;
}

Cor::Cor(double red, double green,double blue)
{
    this -> red = red;
    this -> green = green;
    this -> blue = blue;
}

double Cor::getred(){
    return red;
}

double Cor::getgreen(){
    return green;
}

double Cor::getblue(){
    return blue;
}

Cor Cor::arroba(Cor c)
{
    return Cor(red * c.red,green * c.green,blue * c.blue);
}

Cor Cor::operator + (Cor c)
{
    return Cor(SOMACOMP(red),SOMACOMP(green),SOMACOMP(blue));
}

void Cor::operator += (Cor c)
{
    red += c.red;
    green += c.green;
    blue += c.blue;
}

bool Cor::operator == (Cor c)
{
    return (red == c.red) && (green == c.green) && (blue == c.blue);
}

bool Cor::operator <= (Cor c)
{
    return (red <= c.red) && (green <= c.green) && (blue <= c.blue);
}

Cor Cor::operator - (Cor c)
{
    return Cor(SUBCOMP(red),SUBCOMP(green),SUBCOMP(blue));
}

Cor operator * (double s,Cor c)
{
    return Cor(s * c.red,s * c.green,s * c.blue);
}

Cor Cor::positiva()
{
    return Cor(valabs(red),valabs(green),valabs(blue));
}




