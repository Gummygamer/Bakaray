#ifndef __COR_HPP__

#define __COR_HPP__

class Cor{
protected:
    double red,green,blue;
public:
    friend Cor operator * (double s,Cor c);
    Cor(double,double,double);
    double getred();
    double getgreen();
    double getblue();

    Cor arroba(Cor);

    Cor operator + (Cor);
    Cor operator - (Cor);

    //Cor operator * (double s);

    void operator += (Cor);

    bool operator == (Cor);
    bool operator <= (Cor);

    Cor positiva();
};

#endif
