#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>

using namespace std;

typedef struct servers{
    int tamanhoAtual = 0;
    string docs = "";
}servidores;

int main (int argc, char* argv[]){
    int nServ, cMax, nDoc, nWords;
    int cont;
    int h;
    uint32_t hAux;
    int checksum;
    servidores* vetor;
    string palavraAtual="";
    string palavraAux;
    ifstream entrada;
    ofstream saida;
    entrada.open(argv[1]);
    saida.open(argv[2]);
    entrada >> nServ >> cMax >> nDoc;
    vetor = new servidores[nServ];
    for (int i=0; i<nDoc;i++){
        checksum=0;
        cont=0;
        nWords=0;
        palavraAtual = "";
        entrada >> nWords;
        while(cont!=nWords){
            entrada>>palavraAux;
            for(int j=0;j<palavraAux.length();j++){
                checksum=checksum^palavraAux[j];

            }
            palavraAtual=palavraAtual +" "+ palavraAux;
            cont++;
        }
            h=(7919*checksum)%nServ;
            stringstream stringH;
            stringH << h;
            if(vetor[h].tamanhoAtual!=cMax){
                if(vetor[h].tamanhoAtual==0){
                    vetor[h].docs="[S" +stringH.str()+ "]" + palavraAtual;
                    saida<<vetor[h].docs << "\n";
                    vetor[h].tamanhoAtual++;
                }else{
                    vetor[h].docs=vetor[h].docs+","+palavraAtual;
                    saida<<vetor[h].docs << "\n";
                    vetor[h].tamanhoAtual++;
                }

            }
            else if((vetor[h].tamanhoAtual)==cMax){
                uint32_t k;
                k=1;
                do{
                    hAux=(h+k*(104729*checksum+123))%nServ;
                    k++;
                }while((vetor[hAux].tamanhoAtual)==cMax);
                stringstream stringHaux;
                stringHaux<<hAux;
                saida<<"S"+stringH.str()+"->S"+stringHaux.str()<<"\n";
                if(vetor[hAux].tamanhoAtual==0){
                    vetor[hAux].docs="[S"+stringHaux.str()+"]"+palavraAtual;
                    saida<<vetor[hAux].docs<<"\n";
                    vetor[hAux].tamanhoAtual++;
                }else if(vetor[hAux].tamanhoAtual!=0){
                    vetor[hAux].docs=vetor[hAux].docs+","+palavraAtual;
                    saida<<vetor[hAux].docs<< "\n";
                    vetor[hAux].tamanhoAtual++;
                }
            }
    }
    entrada.close();
    saida.close();
    return 0;
}

