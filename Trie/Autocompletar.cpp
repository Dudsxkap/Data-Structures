#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>

using namespace std;

string* palavrasImpressao;
int tamanhoPI = 0;

typedef struct dicionario{
    struct dicionario** filho;
    string Palavra="";
}no;

no* criarNo(){
    no* x = new no;
    x->filho = new no*[26];

    for(int i=0;i<26;i++){
        x->filho[i] = NULL;
    }

    return x;
}

int indice(string palavra, uint32_t cont){
    int index = palavra[cont];
    return index-97;
}

void inserir (no** x, string palavra, uint32_t cont){
    if((*x) == NULL){
        (*x) = criarNo();
    }
    if(cont == palavra.length()) {
        (*x)->Palavra = palavra;
    }else{
        inserir (&((*x)->filho[indice(palavra,cont)]),palavra,cont + 1);
    }
}

void printarSinonimos(string palavra,ofstream* saida){
    *saida<<palavra<<":";
    if(tamanhoPI==0){
        *saida<<"-";
    }else if(tamanhoPI>0){
        for(int i=0;i<tamanhoPI;i++){
            if(i==0){
                *saida<<palavrasImpressao[i];
            }else{
                *saida<<","<<palavrasImpressao[i];
            }
        }
    }
    *saida<<endl;
}

void addPalavra(string palavra){
    int verificador=0;
    for(int i=0;i<tamanhoPI;i++){
        if(palavrasImpressao[i]==palavra){
            verificador=1;
            break;
        }
    }
    if(verificador==0){
        palavrasImpressao[tamanhoPI]=palavra;
        tamanhoPI++;
    }
}

void acharFilhos(no* x, uint32_t contAtual, uint32_t contPalavra){
    if(x->Palavra!=""){
        addPalavra(x->Palavra);
    }
    if(contAtual!=contPalavra){
        for(int i=0;i<26;i++){
            if(x->filho[i]!=NULL){
                acharFilhos(x->filho[i],contAtual+1,contPalavra);
            }
        }
    }
}

void busca (no* x, string palavra, uint32_t cont,ofstream* saida) {
    if(x != NULL ) {
        if(cont < palavra.length()){
            if (x->filho[indice(palavra, cont)] != NULL){
                acharFilhos(x->filho[indice(palavra, cont)],cont+1,(cont+1)*2);
            }
            busca (x->filho[indice(palavra, cont)], palavra, cont + 1,saida);
        }
    }
}

int main (int argc, char* argv[]){
    int qntTermos,qntBuscas;
    string palavraAux;
    string buscaAux;
    ifstream entrada;
    ofstream saida;
    entrada.open(argv[1]);
    saida.open(argv[2]);
    no* inicio = NULL;
    entrada>>qntTermos;
    for(int i=0; i<qntTermos;i++){
        entrada>>palavraAux;
        inserir(&inicio,palavraAux,0);
    }
    entrada>>qntBuscas;
    palavrasImpressao = new string[qntTermos];
    for(int i=0; i<qntBuscas;i++){
        tamanhoPI=0;
        entrada>>buscaAux;
        busca(inicio,buscaAux,0,&saida);
        printarSinonimos(buscaAux,&saida);
    }
    entrada.close();
    saida.close();
    return 0;
}
