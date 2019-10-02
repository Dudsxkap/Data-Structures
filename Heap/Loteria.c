#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>

using namespace std;

string* ganhadoresMax;
string* ganhadoresMin;

typedef struct apostadores{
    string codigo = "";
    int totalAcertos=0;
}apostadores;

int compare(int ctrl, int* nSorteados){
    int acertos=0;
    for(int k=0;k<10&&acertos==0;k++){
        if(ctrl==nSorteados[k]){
            acertos++;
        }
    }
    return acertos;
}

void busca(int i, int nApostas, int* ganhadores, int totalAcertos, string* vetorGanhadores, apostadores* vetorApostadores){
    if(i < nApostas){
        if(vetorApostadores[i].totalAcertos == totalAcertos){
            vetorGanhadores[*ganhadores] = vetorApostadores[i].codigo;
            *ganhadores += 1;
            busca((2*i) + 1,nApostas, ganhadores, totalAcertos, vetorGanhadores, vetorApostadores);
            busca((2*i) + 2,nApostas, ganhadores, totalAcertos, vetorGanhadores, vetorApostadores);
        }
    }
}

void troca(apostadores* heap, uint32_t P, uint32_t posicao){
    apostadores aux = heap[posicao];
    heap[posicao]=heap[P];
    heap[P]=aux;
}

void heapifyMax(apostadores* heap, uint32_t tamanho, uint32_t posicao){
    uint32_t P = posicao;
    uint32_t E = (2*posicao) + 1;
    uint32_t D = (2*posicao) + 2;
    if(E<tamanho && heap[E].totalAcertos>heap[P].totalAcertos){
        P=E;
    }if(D<tamanho && heap[D].totalAcertos>heap[P].totalAcertos){
        P=D;
    }
    if(P!=posicao){
        troca(heap,P,posicao);
        heapifyMax(heap,tamanho,P);
    }
}

void heapifyMin(apostadores* heap, uint32_t tamanho, uint32_t posicao){
    uint32_t P = posicao;
    uint32_t E = (2*posicao) + 1;
    uint32_t D = (2*posicao) + 2;
    if(E<tamanho && heap[E].totalAcertos<heap[P].totalAcertos){
        P=E;
    }if(D<tamanho && heap[D].totalAcertos<heap[P].totalAcertos){
        P=D;
    }
    if(P!=posicao){
        troca(heap,P,posicao);
        heapifyMin(heap,tamanho,P);
    }
}

int main (int argc, char* argv[]){
    int premioTotal,nApostas,ctrl, testeIgual,premioMax,premioMin;
    int maxAcertos,minAcertos;
    int nMaxGanhadores=0,nMinGanhadores=0;
    int nSorteados[10];
    apostadores* heap;
    apostadores* heapMin;
    ifstream entrada;
    ofstream saida;
    entrada.open(argv[1]);
    saida.open(argv[2]);
    entrada>>premioTotal>>nApostas;
    ganhadoresMax = new string[nApostas];
    ganhadoresMin = new string[nApostas];
    for(int i=0;i<10;i++){
        entrada>>nSorteados[i];
    }

    heap = new apostadores[nApostas];
    heapMin = new apostadores[nApostas];

    for(int i=0;i<nApostas;i++){
        ctrl=0;
        entrada>>heap[i].codigo;
        heapMin[i].codigo = heap[i].codigo;
        for(int j=0;j<15;j++){
            entrada>>ctrl;
            testeIgual=compare(ctrl,nSorteados);
            if(testeIgual==1){
                heap[i].totalAcertos++;
                heapMin[i].totalAcertos++;
            }
        }
    }
    int iHeapMax=((nApostas-1)-1)/2;

    for(iHeapMax;iHeapMax>=0;iHeapMax--){
        heapifyMax(heap,nApostas,iHeapMax);
    }

    maxAcertos=heap[0].totalAcertos;

    busca(0,nApostas,&nMaxGanhadores,maxAcertos,ganhadoresMax,heap);
    int iHeapMin=((nApostas-1)-1)/2;
    for(iHeapMin;iHeapMin>=0;iHeapMin--){
        heapifyMin(heapMin,nApostas,iHeapMin);
    }

    minAcertos=heapMin[0].totalAcertos;

    busca(0,nApostas,&nMinGanhadores,minAcertos,ganhadoresMin,heapMin);
        premioMax=premioTotal/2;
        premioMin=premioTotal/2;

        premioMax=premioMax/nMaxGanhadores;

        premioMin=premioMin/nMinGanhadores;

    saida<<"["<<nMaxGanhadores<<":"<<maxAcertos<<":"<<premioMax<<"]"<<endl;


    for(int i=0;i<nMaxGanhadores;i++){
        saida<<ganhadoresMax[i]<<endl;
    }


    saida<<"["<<nMinGanhadores<<":"<<minAcertos<<":"<<premioMin<<"]"<<endl;

    for(int i=0;i<nMinGanhadores;i++){
        saida<<ganhadoresMin[i]<<endl;
    }

    entrada.close();
    saida.close();
    return 0;
}

