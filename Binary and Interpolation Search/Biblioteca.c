#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct livro{

    char titulo[101];
    char autor[51];
    long long int isbn;

} livro;

int binaria( livro * v, int i, int j, long long int x, int *contBin) {
    int p = (i + j) / 2;
    if(j < i){
        return -1;
    }else if(v[p].isbn == x){
        return p;
    }else if(v[p].isbn < x){
        *contBin=*contBin+1;
        return binaria(v, p + 1, j, x, contBin);
    }else{
        *contBin=*contBin+1;
        return binaria(v, i, p - 1, x, contBin);
    }
}

long long int interpolada( livro * v, int i, int j, long long int x, int* contInt) {
    if((j-i+1)==0){
        return -1;
    }
    *contInt = *contInt+1;
    long long int p = i+((v[j].isbn-v[i].isbn)%(j-i+1));
    if(j<i){
        return -1;
    }else if(v[p].isbn == x){
        return p;
    }else if(v[p].isbn < x){
        return interpolada(v, p + 1, j, x,contInt);
    }else{
        return interpolada(v, i, p - 1, x,contInt);
    }
}

int main (int argc, char* argv[]){
    char tituloAux[101], autorAux[51];
    int nLivros,nPesquisas,contScan=0;
    int contBin,contInt, winBin=0, winInt=0, mdBin=0, mdInt=0;
    long long int isbnAux;
    FILE *arqIn,*arqOut;
    livro* vetor;
    arqIn = fopen(argv[1],"r");
    arqOut = fopen(argv[2],"w");
    while(!feof(arqIn)) {
        if(contScan==0){
            fscanf(arqIn,"%d",&nLivros);
            vetor = (livro*) malloc(nLivros*sizeof(livro));
            contScan++;
        }else if(contScan==1){
            int contLivros=0;
            while(contLivros<nLivros){
                fscanf(arqIn,"%lld %[^&]s", &isbnAux, autorAux);
                fscanf(arqIn,"&%[^\n]s",tituloAux);
                fflush(stdin);
                strcpy(vetor[contLivros].autor, autorAux);
                strcpy(vetor[contLivros].titulo, tituloAux);
                vetor[contLivros].isbn=isbnAux;
                contLivros++;
            }
            contScan++;
        }else if(contScan==2){
            fscanf(arqIn,"%d",&nPesquisas);
            contScan++;
        }else if(contScan==3){
            contInt=0;
            contBin=1;
            int index;
            fscanf(arqIn,"%lld", &isbnAux);
            binaria(vetor,0,nLivros-1,isbnAux,&contBin);
            index = interpolada(vetor,0,nLivros-1,isbnAux,&contInt);
            if(index>-1){
                fprintf(arqOut,"[%lld]B=%d,I=%d:Autor:%s,Title:%s\n",vetor[index].isbn,contBin,contInt,vetor[index].autor,vetor[index].titulo);
            }else if(index <=-1){
                fprintf(arqOut,"[%lld]B=%d,I=%d:ISBN_NOT_FOUND\n",isbnAux,contBin,contInt);
            }
            if(contBin<contInt){
                winBin++;
            }else if(contInt<=contBin){
                winInt++;
            }
            mdBin=mdBin+contBin;
            mdInt=mdInt+contInt;
        }
    }
    fprintf(arqOut,"BINARY=%d:%d\n",winBin,mdBin/nPesquisas);
    fprintf(arqOut,"INTERPOLATION=%d:%d\n",winInt,mdInt/nPesquisas);
    fclose(arqIn);
    fclose(arqOut);
    return 0;
}

