#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    char nome[51];
    struct no *proximo, *anterior;
}amigo;

 amigo *atual, *cabeca, *cauda, *aux, *aux2, *aux1;
 int tamanho;
 char nArq[51];

 int comparar(){
        for(int i=0;i<tamanho;i++){
            aux=cabeca;
            cabeca=cabeca->proximo;
            if(strcmp(nArq,aux->nome)){
                return 1;
            }
        }
        return 0;
 }

 int add (FILE *arqOut){
    aux2=cabeca;
     for(int i=0;i<tamanho;i++){
            aux1=aux2->anterior;
            aux=aux1;
            aux1=aux2;
            aux2=aux2->proximo;
            if(strcmp(nArq,aux1->nome)==0){
                fprintf(arqOut,"[ERROR] ADD %s\n",&nArq);
                return 0;
            }
     }
    if(tamanho==0){
        atual=(amigo*) malloc(sizeof(amigo));
        strcpy(atual->nome, nArq);
        cabeca=atual;
        cauda=atual;
        atual->proximo=atual;
        atual->anterior=atual;
        fprintf(arqOut,"[ OK  ] ADD %s\n",&nArq);
    }else{
        aux=atual;
        atual=(amigo*) malloc(sizeof(amigo));
        strcpy(atual->nome, nArq);
        cauda=atual;
        cauda->proximo=cabeca;
        cabeca->anterior=cauda;
        atual->proximo=cabeca;
        atual->anterior=aux;
        aux->proximo=atual;
        fprintf(arqOut,"[ OK  ] ADD %s\n",&nArq);
    }
    tamanho++;
    return 0;
 }

 int remover(FILE *arqOut){
     aux2=cabeca;
     for(int i=0;i<tamanho;i++){
            aux1=aux2->anterior;
            aux=aux1;
            aux1=aux2;
            aux2=aux2->proximo;
            if(strcmp(nArq,aux1->nome)==0){
                amigo *pf;
                pf=aux1;
                aux->proximo=aux2;
                aux2->anterior=aux;
                if(i==0){
                    cabeca=aux2;
                }else if(i==tamanho-1){
                    cauda=aux;
                    atual=aux;
                }
                free(pf);
                fprintf(arqOut,"[ OK  ] REMOVE %s\n",&nArq);
                tamanho--;
                return 0;
            }
     }
     fprintf(arqOut,"[ERROR] REMOVE %s\n",&nArq);
     return 0;
 }

 int mostrar(FILE *arqOut){
    aux2=cabeca;
    for(int i=0;i<tamanho;i++){
            aux1=aux2->anterior;
            aux=aux1;
            aux1=aux2;
            aux2=aux2->proximo;
            if(strcmp(nArq,aux1->nome)==0){
                fprintf(arqOut,"[ OK  ] %s<-%s->%s\n",&aux1->anterior->nome,&aux1->nome,&aux1->proximo->nome);
                return 0;
            }
     }
     fprintf(arqOut,"[ERROR] ?<-%s->?\n",&nArq);
     return 0;
 }

int main (int argc, char* argv[]){
    char comando[7];
    FILE *arqIn,*arqOut;
    arqIn = fopen (argv[1],"r");
    arqOut = fopen (argv[2],"w");
    while(!feof(arqIn)) {
        fscanf(arqIn,"%s %[^\n]s",&comando,&nArq);
        if(strcmp(comando,"ADD")==0){
            add(arqOut);
        }else if(strcmp(comando,"REMOVE")==0){
            remover(arqOut);
        }else if(strcmp(comando,"SHOW")==0){
            mostrar(arqOut);
        }
        fflush(stdin);
    }
    fclose(arqIn);
    fclose(arqOut);
    return 0;
}
