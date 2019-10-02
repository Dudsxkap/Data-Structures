#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

typedef struct pessoas{
    string nome = "";
}pessoas;

typedef struct orgao{
    string nomeOrg = "";
    int atendentes;
    int jovemAtual=0;
    int idosoAtual=0;
    int qntIdosos=0;
    int qntJovens=0;
    pessoas** idosos;
    pessoas** jovens;
}orgao;

int main (int argc, char* argv[]){
    int totalPessoas=0;
    int qntOrg,qntPessoas;
    string auxLinha,auxOrg,auxNome;
    string idadeArq;
    int auxIdade;
    int parametro,paramAux;
    int cont;
    ofstream saida;
    ifstream entrada;
    entrada.open(argv[1]);
    saida.open(argv[2]);
    entrada>>qntOrg;
    orgao* principal = new orgao[qntOrg];
    for(int i=0;i<qntOrg;i++){
        entrada>>principal[i].nomeOrg;
        entrada>>principal[i].atendentes;
    }
    entrada>>qntPessoas;
    entrada.ignore();

    for(int i=0;i<qntOrg;i++){
        principal[i].idosos = new pessoas*[qntPessoas];
        principal[i].jovens = new pessoas*[qntPessoas];
    }

    for(int i=0;i<qntPessoas;i++){
        cont=0;
        getline(entrada,auxLinha);
        parametro = auxLinha.find("|");
        auxOrg=auxLinha.substr(0,parametro);
        paramAux=parametro;
        parametro = auxLinha.find("|",paramAux+1);
        auxNome = auxLinha.substr(paramAux+1,parametro-paramAux-1);
        idadeArq = auxLinha.substr(parametro+1);
        auxIdade = atoi(idadeArq.c_str());

        pessoas *pessoa = new pessoas;
        pessoa->nome = auxNome;

        for(int j=0;j<qntOrg && cont==0;j++){
            if(principal[j].nomeOrg==auxOrg){
                if(auxIdade>59){
                    principal[j].idosos[principal[j].qntIdosos] = pessoa;
                    principal[j].qntIdosos++;
                }if(auxIdade<60){
                    principal[j].jovens[principal[j].qntJovens] = pessoa;
                    principal[j].qntJovens++;
                }
            cont++;
            }
        }
    }

    int i=0;
    while(totalPessoas!=qntPessoas){
       // for(int i=0;i<qntOrg;i++){
            int atendentesAux=0;
            int entrou=0;
            for(int j=0;j<principal[i].atendentes;j++){
                if(principal[i].idosoAtual!=principal[i].qntIdosos){
                    if(atendentesAux==0){
                        saida<<principal[i].nomeOrg<<":";
                    }else if(atendentesAux>0){
                        saida<<",";
                    }
                    saida<<principal[i].idosos[principal[i].idosoAtual]->nome;
                    principal[i].idosoAtual++;
                    totalPessoas++;
                    entrou++;
                }else if(principal[i].jovemAtual!=principal[i].qntJovens){
                    if(atendentesAux==0){
                        saida<<principal[i].nomeOrg<<":";
                    }else if(atendentesAux>0){
                        saida<<",";
                    }
                    saida<<principal[i].jovens[principal[i].jovemAtual]->nome;
                    principal[i].jovemAtual++;
                    totalPessoas++;
                    entrou++;
                }
                atendentesAux++;
            }
            if(entrou!=0){
                saida<<endl;
            }
        //}
        i++;
        if(i==qntOrg){
            i=0;
        }
    }
    saida.close();
    entrada.close();
    return 0;
}

