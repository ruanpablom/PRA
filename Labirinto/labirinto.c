#include "labirinto.h"
#include "listaencadeada.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROARQ -1
#define ERROALLOC -2
#define COL 36
#define LIN 10


int main(){
    char **lab;
    int i,j;
    ListaEncadeada *lista;
    int **vertices;
    int cont=1;

    lab = (char**)malloc(LIN*sizeof(char*));
    if(lab == NULL)return ERROALLOC;    
    vertices = (int**)malloc(LIN*sizeof(int*));
    if(vertices == NULL)return ERROALLOC;
    for(i=0;i<LIN;i++){
        lab[i]=(char*)malloc(COL*sizeof(char));
        if(lab[i]==NULL)return ERROALLOC;
        vertices[i]=(int*)malloc(COL*sizeof(int));
        if(vertices[i]==NULL)return ERROALLOC;

    }
    carga("labirinto_test_1", lab);
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            printf("%c ",lab[i][j]);
            vertices[i][j]=cont;
            cont++;
        }
        printf("\n");
    }
    return 0;
}

int carga(char *nomeArquivo,char **lab){
    int i=0,j;
    FILE *arq = fopen(nomeArquivo,"r");
    if(arq==NULL){
        printf("Falha ao ler o arquivo!\n");
        return ERROARQ;
    }
    printf("%i\n",LIN);
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            fscanf(arq,"%c",&lab[i][j]);
        }
    } 
    return 1 ;
}
    
int *caminhoMinimo(char **labirinto){
    ListaEncadeada **listas;
    int *caminho;
    int inicio_x,inicio_y,fim_x,fim_y;

    listas=(ListaEncadeada**)malloc(sizeof(ListaEncadeada*));
    if(listas==NULL)return 0;
    posInicio(&inicio_x,&inicio_y,labirinto);
    posSaida(&fim_x,&fim_y,labirinto);
    
    

    return caminho;
}

int posInicio(int *x, int *y, char **lab){
    int i,j;
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            if(lab[i][j]=='S'){
                *x=i;
                *y=j;
                return 1;
            }
        }
    }

    return 0;
}

int posSaida(int *x, int *y, char **lab){
    int i,j;
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            if(lab[i][j]=='E'){
                *x=i;
                *y=j;
                return 1;
            }
        }
    }

    return 0;
}

int pCima(int x, int y, char **lab, int **v){
    if((x-1) < 0 | lab[x-1][y]=='#')return 0;
    else return v[x-1][y];
}

int pBaixo(int x, int y, char **lab, int **v){
    if((x+1) > LIN-1 | lab[x+1][y]=='#')return 0;
    else return v[x-1][y];
}

int pDireita(int x, int y, char **lab, int **v){
    if((y+1) > COL-1 | lab[x][y+1]=='#')return 0;
    else return v[x][y+1];
}

int pEsquerda(int x, int y, char **lab, int **v){
    if((y-1) < 0 | lab[x][y-1]=='#')return 0;
    else return v[x][y-1];
}
