#ifndef __ATENUACAO_HPP__

#define __ATENUACAO_HPP__

class Atenuacao{
private:
    double a,b,c;
public:
    Atenuacao(double,double,double);
    double geta();
    double getb();
    double getconst();
};

#endif
