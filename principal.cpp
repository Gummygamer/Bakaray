#include "atenuacao.hpp"
//#include "camera.hpp"
#include "cena.hpp"
#include "cor.hpp"
#include "esfera.hpp"
#include "plano.hpp"
#include "triangulo.hpp"
#include "cone.hpp"
#include "luz.hpp"
#include "material.hpp"
#include "pontovetorcamera.hpp"
#include "renderizador.hpp"
#include "resolucao.hpp"

#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

int W,H; //tamanho da janela
Cena* cena;
Camera* camera;
RenderizadorBakaray* renderizador;

Cor** imagem;

Atenuacao* RecebeInfoAtenuacao(void)
{
    double a,b,c;

    cin >> c;
    cin >> b;
    cin >> a;

    Atenuacao* novaAtenuacao = new Atenuacao(a,b,c);

    return novaAtenuacao;
}

Ponto* RecebeInfoPonto()
{
    float x,y,z;

    cin >> x;

    cin >> y;

    cin >> z;

    Ponto* novoPonto = new Ponto(x,y,z);

    return novoPonto;
}


Cor* RecebeInfoCor()
{
    double red,green,blue;

    cin >> red;
    cin >> green;
    cin >> blue;

    Cor* novaCor = new Cor(red,green,blue);

    return novaCor;
}

Material* RecebeInfoMaterial()
{
    Cor* ambiente = RecebeInfoCor();
    Cor* difusa = RecebeInfoCor();
    Cor* especular = RecebeInfoCor();
    double brilho,rugosidade;

    cin >> brilho;

    cin >> rugosidade;

    Material* novoMaterial = new Material(ambiente,difusa,especular,brilho,rugosidade);

    return novoMaterial;
}

Objeto* RecebeinfoEsfera()
{
    Ponto* ponto = RecebeInfoPonto();
    double raio;

    cin >> raio;

    Material* material = RecebeInfoMaterial();

    return (Objeto*) new Esfera(ponto,material,raio);
}

Objeto* RecebeinfoPlano()
{
    Ponto* n1 = RecebeInfoPonto();

    Ponto* n2 = RecebeInfoPonto();

    Material* material = RecebeInfoMaterial();

    return (Objeto*) new Plano(n1,n2,material);
}

Objeto* RecebeinfoTriangulo()
{
    Ponto* p0 = RecebeInfoPonto();

    Ponto* p1 = RecebeInfoPonto();

    Ponto* p2 = RecebeInfoPonto();

    Material* material = RecebeInfoMaterial();

    return (Objeto*) new Triangulo(p0,p1,p2,material);
}

Objeto* RecebeinfoTrianguloRGB()
{
    Ponto* p0 = RecebeInfoPonto();

    Ponto* p1 = RecebeInfoPonto();

    Ponto* p2 = RecebeInfoPonto();

    int red,green,blue;

    cin >> red;

    cin >> green;

    cin >> blue;

    Material* material = new Material(red,green,blue);

    return (Objeto*) new Triangulo(p0,p1,p2,material);
}

Objeto* RecebeinfoCone()
{
    Ponto* p1 = RecebeInfoPonto();

    double h;

    cin >> h;

    Material* material = RecebeInfoMaterial();

    return (Objeto*) new Cone(p1,h,material);
}


Objeto* RecebeinfoObjeto()
{
    char tipoobj;

    cin >> tipoobj;

    switch (tipoobj)
    {
    case 'e':
        return RecebeinfoEsfera();
    case 'p':
        return RecebeinfoPlano();
    case 't':
        return RecebeinfoTriangulo();
    case 'T':
        return RecebeinfoTrianguloRGB();
    case 'c':
        return RecebeinfoCone();
    default:
        return 0;
    }
}


void init()
{
    int numObjetos;
    int i; //Contador para loop

    cin >> numObjetos;

    Objeto** vetorObjetos = (Objeto**) malloc(numObjetos*sizeof(Objeto*));

    for (i = 0; i < numObjetos; ++i)
    {
        vetorObjetos[i] = RecebeinfoObjeto();
    }

    int numLuzes;

    cin >> numLuzes;

    Luz** vetorLuzes = (Luz**) malloc(numLuzes*sizeof(Luz*));

    for (i = 1; i <= numLuzes; i++)
    {
        Ponto* posicao = RecebeInfoPonto();
        Cor* ambiente = RecebeInfoCor();
        Cor* difusa = RecebeInfoCor();
        Cor* especular = RecebeInfoCor();
        Atenuacao* a = RecebeInfoAtenuacao();

        vetorLuzes[i - 1] = new Luz(posicao,ambiente,difusa,especular,a);
    }

    cena = new Cena((Objeto**) vetorObjetos,vetorLuzes,numObjetos,numLuzes);

    cin >> W;

    cin >> H;

    Ponto* Observador = RecebeInfoPonto();
    Ponto* Destino = RecebeInfoPonto();
    Vetor* Direcao = new Vetor(Destino -> getx() - Observador -> getx(),
                               Destino -> gety() - Observador -> gety(),
                               Destino -> getz() - Observador -> getz());

    double ux,uy,uz;

    cin >> ux;

    cin >> uy;

    cin >> uz;

    double distancia;
    cin >> distancia;

    camera = new Camera(Observador,Direcao,new Vetor(ux,uy,uz),distancia);

    srand(time(0));
}

void pinta(int i,int j,Cor c)
{
    float pixel[3] = {(float) c.getred(),(float) c.getgreen(),(float) c.getblue()};
    glRasterPos2i(j - W/2,H/2 - i);
    glDrawPixels(1,1,GL_RGB,GL_FLOAT,pixel);
}

void desenha()
{
    int l,c;

    for (l = 0; l < H; ++l)
    {
        for (c = 0; c < W; ++c)
        {
            pinta(l,c,imagem[l][c]);
        }
    }
}

void display(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-W/2,W/2,-H/2,H/2);
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT);
    desenha();
    glFlush();
    //exit(0);
}

int main(int argc,char **argv)
{
    init();
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(W,H);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Bakaray");
    glutDisplayFunc(display);

    bool modo = false;

    if (argc > 1) modo = true;

    Resolucao* resolucao = new Resolucao(W,H);
    renderizador = new RenderizadorBakaray(camera,resolucao,cena,modo);

    imagem = renderizador -> getImagem();

    glutMainLoop();
    return 1;
}
