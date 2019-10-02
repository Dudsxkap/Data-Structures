#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>

using namespace std;

uint32_t myrand () {
    static uint32_t next = 1;
    next = next * 1103515245 + 12345;
    return next ;
}

uint32_t gFunc (uint32_t posicao){
    return posicao + (-1 + myrand()%3);
}

int main (int argc, char* argv[]){
    uint32_t qntMatrizes;
    uint32_t alturaAux, larguraAux;
    uint32_t inicialX, inicialY;
    uint32_t xAux,yAux;
    uint32_t qntPacientes;
    uint32_t** regiao;
    ifstream entrada;
    ofstream saida;
    entrada.open(argv[1]);
    saida.open(argv[2]);
    entrada>>qntMatrizes;
    for(int i=1;i<=qntMatrizes;i++){
        entrada>>alturaAux>>larguraAux;
        entrada>>inicialX>>inicialY;

        regiao = new uint32_t*[alturaAux]();
        for(int j=0;j<alturaAux;j++){
            regiao[j] = new uint32_t [larguraAux]();
        }
        regiao[inicialX][inicialY]=1;
        xAux=inicialX;
        yAux=inicialY;
        qntPacientes=alturaAux * larguraAux;
        saida<<i<<":"<<"("<<inicialX<<","<<inicialY<<")";
        if(qntPacientes>1){
            saida<<";";
        }
        for(int j=1;j<qntPacientes&&qntPacientes>1;j++){
              do{
                do{
                    xAux=gFunc(inicialX);

                }while(xAux>=alturaAux);
                do{
                    yAux=gFunc(inicialY);

                }while(yAux>=larguraAux);
                inicialX=xAux;
                inicialY=yAux;
              }while(regiao[xAux][yAux]!=0);
              regiao[xAux][yAux]=1;
              saida<<"("<<inicialX<<","<<inicialY<<")";
              if(j!=qntPacientes-1){
                saida<<";";
              }
        }
        saida<<endl;
    }
    entrada.close();
    saida.close();
    return 0;
}
