#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    int tamanho;
    int posicao;
    char nome[51];
    char tipo[4];
    struct no *esquerda;
    struct no *direita;
}no;

no *cabeca = NULL,*atual;
int tamanho=0;
int cont = 0;

int add(char *nomeAux, char *tipoAux, int tamanhoAux, int posicaoAux){
    if(tamanho==0){
        strcpy(atual->nome, nomeAux);
        strcpy(atual->tipo, tipoAux);
        atual->tamanho=tamanhoAux;
        atual->posicao=posicaoAux;
        atual->esquerda=NULL;
        atual->direita=NULL;
        cabeca=atual;
        tamanho++;
    }

    else if(tamanho!=0){
        no *noAtual=cabeca;
        strcpy(atual->nome, nomeAux);
        strcpy(atual->tipo, tipoAux);
        atual->tamanho=tamanhoAux;
        atual->posicao=posicaoAux;
        atual->esquerda=NULL;
        atual->direita=NULL;

        while(cont == 0){
            if(strcmp(atual->nome,noAtual->nome)==0){
                if(strcmp(noAtual->tipo,"rw")==0){
                    strcpy(noAtual->tipo, tipoAux);
                    noAtual->posicao = posicaoAux;
                    noAtual->tamanho = tamanhoAux;
                }
                return 0;
            }else if(strcmp(atual->nome,noAtual->nome)<0){
                if(noAtual->esquerda==NULL){
                    noAtual->esquerda=atual;
                    return 0;
                }else{
                    noAtual=noAtual->esquerda;
                }
            }else if(strcmp(atual->nome,noAtual->nome)>0){
                if(noAtual->direita==NULL){
                    noAtual->direita=atual;
                    return 0;
                }else{
                    noAtual=noAtual->direita;
                }
            }
        }
    }
}

void emOrdem(no *noAtual, FILE *arqOut){
    if(noAtual!=NULL){
        emOrdem(noAtual->esquerda,arqOut);
        if(noAtual->tamanho==1){
            fprintf(arqOut,"%d %s %s %d byte\n",noAtual->posicao,noAtual->nome,noAtual->tipo,noAtual->tamanho);
        }else if(noAtual->tamanho!=1){
            fprintf(arqOut,"%d %s %s %d bytes\n",noAtual->posicao,noAtual->nome,noAtual->tipo,noAtual->tamanho);
        }
        emOrdem(noAtual->direita,arqOut);
    }
}

void preOrdem(no *noAtual, FILE *arqOut){
    if(noAtual!=NULL){
        if(noAtual->tamanho==1){
            fprintf(arqOut,"%d %s %s %d byte\n",noAtual->posicao,noAtual->nome,noAtual->tipo,noAtual->tamanho);
        }else if(noAtual->tamanho!=1){
            fprintf(arqOut,"%d %s %s %d bytes\n",noAtual->posicao,noAtual->nome,noAtual->tipo,noAtual->tamanho);
        }
        preOrdem(noAtual->esquerda,arqOut);
        preOrdem(noAtual->direita,arqOut);
    }
}

void posOrdem(no *noAtual, FILE *arqOut){
    if(noAtual!=NULL){
        posOrdem(noAtual->esquerda,arqOut);
        posOrdem(noAtual->direita,arqOut);
        if(noAtual->tamanho==1){
            fprintf(arqOut,"%d %s %s %d byte\n",noAtual->posicao,noAtual->nome,noAtual->tipo,noAtual->tamanho);
        }else if(noAtual->tamanho!=1){
            fprintf(arqOut,"%d %s %s %d bytes\n",noAtual->posicao,noAtual->nome,noAtual->tipo,noAtual->tamanho);
        }
    }
}

int main(int argc, char* argv[]){
    int nmrArq, pArq=0;
    int tamanhoArq;
    int contFeof = 0,contLinha=0;
    char nomeArq[51], tipoArq[4];
    FILE *arqIn,*arqOut;
    arqIn = fopen (argv[1],"r");
    arqOut = fopen (argv[2],"w");
    while(!feof(arqIn)) {
        if(contLinha==0){
            fscanf(arqIn,"%d",&nmrArq);
            contLinha++;
            contFeof=nmrArq;
        }else{
            fscanf(arqIn,"%s %s %d",nomeArq,tipoArq,&tamanhoArq);
            atual = (no*)malloc(sizeof(no));
            add(nomeArq, tipoArq, tamanhoArq, pArq);
            pArq++;
            contFeof--;
        }
        if(contFeof==0){
            break;
        }
        fflush(stdin);
    }
    fprintf(arqOut,"EPD:\n");
    emOrdem(cabeca,arqOut);
    fprintf(arqOut,"PED:\n");
    preOrdem(cabeca,arqOut);
    fprintf(arqOut,"EDP:\n");
    posOrdem(cabeca,arqOut);
    fclose(arqIn);
    fclose(arqOut);
    return 0;
}
