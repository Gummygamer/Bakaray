#include "renderizador.hpp"
#include <GL/glut.h>
#include <iostream>
#include <math.h>

#define PERTO 0.1

#define PERTOCOR 0.01

#define NIVEL 2

using namespace std;

RenderizadorBakaray::RenderizadorBakaray(Camera* camera,Resolucao* res,Cena* cena,bool modoheuristico)
{
    this -> camera = camera;

    this -> modoheuristico = modoheuristico;

    cena -> reescreve(camera);

    tamx = res -> getx();
    tamy = res -> gety();

    xpixel0 = (float) -tamx;
    xpixel0 /= 2;
    xpixel0 += 0.5;

    ypixel0 = (float) tamy;
    ypixel0 /= 2;
    ypixel0 -= 0.5;

    objetos = cena -> getObjetos();
    luzes = cena -> getLuzes();

    numobjetos = cena -> getNumObjetos();
    numluzes = cena -> getNumLuzes();

    pzero = new Ponto(0,0,0);

    imagem = (Cor**) malloc(tamy * sizeof(Cor*));

    int cont;

    for (cont = tamy - 1; cont >= 0; cont--)
    {
        imagem[cont] = (Cor*) malloc(tamx * sizeof(Cor));
    }

    geraimagem();
    //czero = new Cor(0,0,0);
}

void RenderizadorBakaray::pintapixel(int i,int j,Cor c)
{
    /* float pixel[3] = {(float) c.getred(),(float) c.getgreen(),(float) c.getblue()};
    glRasterPos2i(i,j);
    glDrawPixels(1,1,GL_RGB,GL_FLOAT,pixel); */

    imagem[i][j] = c;
}


void RenderizadorBakaray::geraimagemheuristicamente()
{
    Cor anterior = Cor(0,0,0);

    Cor atual = Cor(0,0,0);

    int pulo = 0;

    int pulovolta = 0;

    int pulopotencial = 0;

    if (numobjetos > 0 && numluzes > 0)
    {
        //cout << xpixel << "/" << ypixel << endl;

        //tamx /= 2;
        //tamy /= 2;

        int l,c;

        for (l = 0; l < tamy; ++l)
        {
            for (c = 0; c < tamx; ++c)
            {

                if (!pulovolta)
                {
                    if (!pulo)
                    {
                        anterior = atual;
                        atual = lancaraio(l,c);

                        pintapixel(l,c,atual);

                        if ((!(anterior == Cor(0,0,0)) && ((atual - anterior).positiva() <= Cor(PERTOCOR,PERTOCOR,PERTOCOR))))
                        {
                            pulopotencial++;
                            pulo = pulopotencial;
                        }
                        else
                        {
                            pulovolta = pulopotencial;
                            if (c >= pulopotencial) c -= pulopotencial;
                            pulopotencial = 0;
                        }
                    }
                    else
                    {
                        pulo--;

                        pintapixel(l,c,anterior);
                    }
                }
                else
                {
                    //anterior = atual;
                    atual = lancaraio(l,c);

                    pintapixel(l,c,atual);

                    pulovolta--;
                }

            }
            //xpixel -= c;

            //ypixel -= l;
            //pintapixel(c - tamx/2,tamy/2 - l,lancaraio(l,c));
        }
    }
}

void RenderizadorBakaray::geraimagem1raioporpixel()
{
    int cont;

    if (numobjetos > 0 && numluzes > 0)
    {
        //cout << xpixel << "/" << ypixel << endl;

        //tamx /= 2;
        //tamy /= 2;

        int l,c;

        for (l = 0; l < tamy; ++l)
        {
            for (c = 0; c < tamx; ++c)
            {

                //xpixel -= c;

                //ypixel -= l;
                //pintapixel(c - tamx/2,tamy/2 - l,lancaraio(l,c));
                pintapixel(l,c,lancaraio(l,c));
            }
        }
    }
}

void RenderizadorBakaray::geraimagem()
{
    if (modoheuristico)
    {
        geraimagemheuristicamente();
    }
    else
    {
        geraimagem1raioporpixel();
    }
}

Cor RenderizadorBakaray::iluminacaolocal(Material* mat,Vetor* n,Vetor* v,Ponto* p)
{
    Cor ret = Cor(0,0,0);

    Luz** ilu = luzes;
    //double atenuacaodist;

    for (int k = 0;k < numluzes; k++)
    {

        Ponto* pos = ilu[k] -> getpos();

        float xluz = pos -> getx();
        float yluz = pos -> gety();
        float zluz = pos -> getz();

        //cout << yluz << endl;

        float xl = xluz - p -> getx();
        float yl = yluz - p -> gety();
        float zl = zluz - p -> getz();

        /*Vetor* vp = new Vetor(p);

        Ponto* quasep = new Ponto(vp);*/

        Vetor* lbruto = new Vetor(xl,yl,zl);
        Vetor* l = UNITARIO(lbruto);

	double tluz = lbruto->modulo();

        //vp = Soma(*vp,*(VetorModuloX(n,PERTO)));

        Reta* raiosombra = new Reta(p,l);

        int cont;

        //double interseccao = objetos[0] -> primeiraInterseccao(raiosombra);

        bool escondido = false;

        for (cont = numobjetos - 1; cont >= 0; cont--)
        {
            double valor = objetos[cont] -> primeiraInterseccao(raiosombra);

            //cout << valor << endl;

            if ((valor >= PERTO) && (valor < tluz))
            {
                escondido = true;
                break;
            }
        }

        //cout << interseccao << endl;


        double dist = lbruto -> modulo();

        //cout << dist << endl;

        Atenuacao* atl = ilu[k] -> getaten();
        double a = atl -> geta();
        double b = atl -> getb();
        double c = atl -> getconst();
        double atenuacaodist = 1.0/(a*dist*dist + b*dist + c);

        //cout << c << endl;

        double atenuacaoangular = ProdutoEscalar(*l,*n);

        //double rluz,gluz,bluz,rmat,gmat,bmat;

        if ((atenuacaoangular > 0) && !escondido)
        {
            Cor luzdifusa = *(ilu[k] -> getdif());
            Cor matdifusa = *(mat -> getdif());

            /* rluz = luzdifusa -> getred() * atenuacaodist;
            rmat = matdifusa -> getred();

            rdif += rluz * rmat * atenuacaoangular;

            gluz = luzdifusa -> getgreen() * atenuacaodist;
            gmat = matdifusa -> getgreen();

            gdif += gluz * gmat * atenuacaoangular;

            bluz = luzdifusa -> getblue() * atenuacaodist;
            bmat = matdifusa -> getblue();

            bdif += bluz * gmat * atenuacaoangular; */

            ret += atenuacaoangular * ((atenuacaodist * luzdifusa).arroba(matdifusa)) ;

            Vetor* mid = VetorModuloX(n,2*atenuacaoangular);
            double rx = mid -> getx() - l -> getx();
            double ry = mid -> gety() - l -> gety();
            double rz = mid -> getz() - l -> getz();

            Vetor* rbruto = new Vetor(rx,ry,rz);
            Vetor* r = VetorModuloX(rbruto,1);

            /* double vx = obs -> getx() - p -> getx();
            double vy = obs -> gety() - p -> gety();
            double vz = obs -> getz() - p -> getz();

            Vetor* vbruto = new Vetor(vx,vy,vz);
            Vetor* v = VetorModuloX(vbruto,1); */

            double espelho = ProdutoEscalar(*r,*v);

            if (espelho > 0)
            {

                double brilho = mat -> getbrilho();

                double atenesp = pow(espelho,brilho);

                Cor luzespecular = *(ilu[k] -> getesp());
                Cor matespecular = *(mat -> getesp());

                /*

                        rluz = luzespecular -> getred() * atenuacaodist;
                        rmat = matespecular -> getred();

                        resp += rluz * rmat * atenesp;

                        gluz = luzespecular -> getgreen() * atenuacaodist;
                        gmat = matespecular -> getgreen();

                        gesp += gluz * gmat * atenesp;

                        bluz = luzespecular -> getblue() * atenuacaodist;
                        bmat = matespecular -> getblue();

                        besp += bluz * bmat * atenesp; */

                ret += atenesp * ((atenuacaodist * luzespecular).arroba(matespecular)) ;
            }

            delete lbruto;
            delete l;
            //delete vbruto;
            //delete v;
            delete rbruto;
            delete r;
        }



        Cor luzambiente = *(ilu[k] -> getamb());
        Cor matambiente = *(mat -> getamb());

        /*

            rluz = luzambiente -> getred();
            rmat = matambiente -> getred();

            ramb += rluz * rmat * atenuacaodist;

            gluz = luzambiente -> getgreen();
            gmat = matambiente -> getgreen();

            gamb += gluz * gmat * atenuacaodist;

            bluz = luzambiente -> getblue();
            bmat = matambiente -> getblue();

            bamb += bluz * bmat * atenuacaodist; */

        ret += (atenuacaodist*luzambiente).arroba(matambiente);

    }

    //float pixel[3] = {rdif + resp + ramb,gdif + gesp + gamb,bdif + besp + bamb};

    return ret;

    //glRasterPos2i(i,j);
    //glDrawPixels(1,1,GL_RGB,GL_FLOAT,pixel);
}

Cor RenderizadorBakaray::lancaraio(int l,int c)
{
    float xpixel = xpixel0 + c;
    float ypixel = ypixel0 - l;

    Vetor pixel = Vetor(xpixel,ypixel,camera -> getDistancia());

    /*Vetor* i = camera -> geti();
    Vetor* j = camera -> getj();
    Vetor* k = camera -> getk();

    double ix = i -> getx();
    double iy = i -> gety();
    double iz = i -> getz();

    double jx = j -> getx();
    double jy = j -> gety();
    double jz = j -> getz();

    double kx = k -> getx();
    double ky = k -> gety();
    double kz = k -> getz();

    double xrot = ProdutoEscalar(pixel,Vetor(ix,jx,kx));
    double yrot = ProdutoEscalar(pixel,Vetor(iy,jy,ky));
    double zrot = ProdutoEscalar(pixel,Vetor(iz,jz,kz));

    Ponto* orig = camera -> getPosicao();

    pixel = Vetor(xrot + orig -> getx(),yrot + orig -> gety(),zrot + orig -> getz()); */


    //cout << l << "/" << c << endl;


    //Vetor* diratual = UNITARIO(pixel);

    Reta raio = Reta(pzero,&pixel);

    return lancaraio(&raio,NIVEL);
}

Cor RenderizadorBakaray::lancaraio(Reta* raio,int n)
{
    int cont;

    double interseccao = objetos[0] -> primeiraInterseccao(raio);

    int apintar = 0;

    for (cont = numobjetos - 1; cont >= 1; cont--)
    {
        double valor = objetos[cont] -> primeiraInterseccao(raio);

        if ((valor >= PERTO) && ((valor < interseccao) || (interseccao < PERTO)))
        {
            interseccao = valor;
            apintar = cont;
        }
    }

    //cout << apintar << endl;

    //interseccao = 100;

    //cout << interseccao << endl;

    if (interseccao > 0)
    {
        Ponto* posraio = raio -> getP();

        Objeto* pintado = objetos[apintar];

        Vetor* vinter = VetorModuloX(raio -> getD(),interseccao);

        vinter = Soma(*vinter,*(new Vetor(posraio)));

        Ponto* pinter = new Ponto(vinter);

        //Ponto* pobjeto = menos(pinter,pintado -> getOrigem());

        Vetor* normal = pintado -> getNormalDistorcida(pinter);

        //pintapixel(tamy/2 - l,c - tamx/2,pintada -> getMaterial(),normal,pinter,pzero);
        //pintapixel(c - tamx/2,tamy/2 - l,pintada -> getMaterial(),normal,pinter,pzero);
        //pintapixel(l,c,pintada -> getMaterial(),normal,pinter,pzero);

        Ponto pontov = *(menos(posraio,pinter));

        Vetor* v = UNITARIO(new Vetor(&pontov));

        Vetor antiv = *(ProdutoPorEscalar(v,-1));

        Material* mat = pintado -> getMaterial();

        double reflete = 2*ProdutoEscalar(*v,*normal);

        //if(reflete <= 0) return iluminacaolocal(mat,normal,v,pinter);

        Vetor* r = Soma(*(ProdutoPorEscalar(normal,reflete)),antiv);

        Reta* raioreflexao = new Reta(pinter,r);

        Cor matesp = *(mat -> getesp());

        delete vinter;
        delete r;

        Cor ret = Cor(0,0,0);

        if (!n)
        {
            ret = iluminacaolocal(mat,normal,v,pinter);
        }
        else ret = iluminacaolocal(mat,normal,v,pinter) + lancaraio(raioreflexao,n - 1).arroba(matesp);

        //cout << reflexoes << endl;

        //cout << refdouble;

        delete pinter;
        delete v;
        delete normal;
        delete raioreflexao;

        return ret;

        //return iluminacaolocal(mat,normal,v,pinter) + lancaraio(raioreflexao).arroba(matesp);
    }
    return Cor(0,0,0);
}

Cor** RenderizadorBakaray::getImagem()
{
    return imagem;
}


