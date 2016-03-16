#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    char **lab;
    int i,j;
    int **vertices; 

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
    carga("l_1.in", lab, vertices);
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            printf("%-3i ",vertices[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            printf("%c ",lab[i][j]);
        }
        printf("\n");
    }
    caminhoMinimo(lab,vertices);

    return 0;
}

ListaEncadeada *caminhoInicial(ListaEncadeada **mapa, int **vet, char **lab){
    ListaEncadeada *caminho;
    ListaEncadeada *pilha;
    int tP,indice;
    int qV=qtdVertices(vet);
    Elemento *elemento;

    pilha = criaLista();
    caminho = criaLista();

    int inicio = posInicio(vet,lab);
    int saida = posSaida(vet,lab);

    if(inicio==0 | saida==0)exit(0);

    adicionaNoInicio(pilha,inicio);
    while(1){
        tP = removeElemento(pilha);
        if(tP==saida){
            adicionaNoFim(caminho,tP);
            break;
        }
        indice = procuraNoMapa(mapa,tP,qV);
        elemento = mapa[indice]->cabeca;
        while(elemento!=NULL){
            if(!pertenceALista(pilha,elemento->info) && !pertenceALista(caminho,elemento->info)){
                adicionaNoInicio(pilha,elemento->info);
            }
            elemento = elemento->proximo;
        }
        adicionaNoFim(caminho,tP);
        if(estah_vazia_listaenc(pilha)){
            printf("Não existe Caminho\n");
            exit(0);
        }
        //imprime_lista(pilha);    
    } 
    imprime_lista(caminho);
    return caminho;
}

int pertenceALista(ListaEncadeada *lista, int elemento){
    Elemento *e;
    
    //printf("elemento %i\n",elemento);
    e = lista->cabeca;
    while(e!=NULL){
        if(e->info == elemento)return 1;
        e=e->proximo;
    }
    return 0;
}

int procuraNoMapa(ListaEncadeada **mapa, int elemento, int qV){
    int indice,i;

    for(i=0;i<qV;i++){
        if(mapa[i]->cabeca->info == elemento) return i;
    }
    printf("Não existe lista onde %i éo  cabeça\n,elemento");
    exit(0);
}

ListaEncadeada **mapeamento(int **vertices){
    int i,j;
    int verticeAtual=0;
    int elemento;  
    int qV = qtdVertices(vertices);
    ListaEncadeada **mapa;

    mapa=(ListaEncadeada**)malloc(sizeof(ListaEncadeada*)*qV);
    if(mapa==NULL)exit(0);

    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){ 
            if(vertices[i][j]==INALCANCAVEL)continue;
            //printf("Mapeamento\n");
            mapa[verticeAtual]=criaLista();
            adicionaNoFim(mapa[verticeAtual],vertices[i][j]);

            elemento=pCima(i,j,vertices);
            if(elemento!=0)adicionaNoFim(mapa[verticeAtual],elemento);

            elemento=pBaixo(i,j,vertices);
            if(elemento!=0)adicionaNoFim(mapa[verticeAtual],elemento);
            elemento=pEsquerda(i,j,vertices);
            if(elemento!=0)adicionaNoFim(mapa[verticeAtual],elemento);
            elemento=pDireita(i,j,vertices);
            if(elemento!=0)adicionaNoFim(mapa[verticeAtual],elemento);
            //imprime_lista(mapa[verticeAtual]); 
            verticeAtual++; 
        }
    }
    //imprime_lista(mapa[0]);
    return mapa;
}



ListaEncadeada *caminhoMinimo(char **labirinto,int **vertices){
    ListaEncadeada **mapa;
    ListaEncadeada *caminho;
    int qV;

    mapa = mapeamento(vertices);
    caminho = caminhoInicial(mapa,vertices,labirinto); 

    return caminho;
}

int carga(char *nomeArquivo,char **lab, int **vertices){
    int i=0,j;
    int cont=1;
    FILE *arq = fopen(nomeArquivo,"r");
    if(arq==NULL){
        printf("Falha ao ler o arquivo!\n");
        return ERROARQ;
    }
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            fscanf(arq,"%c",&lab[i][j]);
            if(lab[i][j]=='\n')fscanf(arq,"%c",&lab[i][j]);
            if(lab[i][j]=='#')vertices[i][j]=INALCANCAVEL;
            else vertices[i][j]=cont;
            cont++;
        }
    } 
    return 1 ;
}

int qtdVertices(int **vertices){
    int i,j,count=0;
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            if(!(vertices[i][j]==-10))count++;
        }
    }
    return count;
}

int posInicio(int **vet, char **lab){
    int i,j;
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            if(lab[i][j]=='S'){ 
                return vet[i][j];;
            }
        }
    }

    return 0;
}

int posSaida(int **vet, char **lab){
    int i,j;
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            if(lab[i][j]=='E'){
                return vet[i][j];
            }
        }
    }

    return 0;
}

int pCima(int x, int y, int **v){
    if((x-1) < 0 | v[x-1][y]==INALCANCAVEL)return 0;
    else return v[x-1][y];
}

int pBaixo(int x, int y,  int **v){
    if((x+1) > LIN-1 | v[x+1][y]==INALCANCAVEL)return 0;
    else return v[x+1][y];
}

int pDireita(int x, int y, int **v){
    if((y+1) > COL-1 | v[x][y+1]==INALCANCAVEL)return 0;
    else return v[x][y+1];
}

int pEsquerda(int x, int y, int **v){
    if((y-1) < 0 | v[x][y-1]==INALCANCAVEL)return 0;
    else return v[x][y-1];
}


void printVert(int **vertices){
    int i,j;

    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            printf("%i ",vertices[i][j]);
        }
        printf("\n");
    }
}

void printLab(char **lab){
    int i,j;

    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            printf("%c",lab[i][j]);
        }
        printf("\n");
    }

}

ListaEncadeada *criaLista(){
    ListaEncadeada *lista = (ListaEncadeada*)malloc(sizeof(ListaEncadeada));
    if(lista!=NULL){
        lista->tamanho=0;
        lista->cabeca=NULL;
    }
    return lista;
}

int estah_vazia_listaenc(ListaEncadeada *lista){
    if(lista->tamanho==0) return 1;
    else return 0;
}

void destroi_lista(ListaEncadeada *lista){
    Elemento *atual = lista->cabeca;
    while(atual!=NULL){
        Elemento *aux = atual;
        atual = atual->proximo;
        free(aux);
    }
    lista->tamanho=0;
    lista->cabeca=NULL;
    free(lista);
}

int adicionaNoInicio(ListaEncadeada *lista, int dados){
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    if(novo!=NULL){
        novo->info = dados;
        novo->proximo = lista->cabeca;
        lista->cabeca = novo;
        lista->tamanho++;
        return lista->tamanho;
    }
    else return 0;
}

int adicionaNoFim(ListaEncadeada *lista, int dados){
    if(estah_vazia_listaenc(lista)==1){
        adicionaNoInicio(lista,dados);
    }else{
        Elemento *e = lista->cabeca;
        while(e->proximo!=NULL){
            e = e->proximo;
        }
        Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
        if(novo!=NULL){
            novo->info = dados;
            novo->proximo = NULL;
            e->proximo = novo;
            lista->tamanho++;
            return lista->tamanho;
        }
    }
    return 0;
}

int removeElemento(ListaEncadeada *lista){
    int elemento;
    Elemento *e;

    e = lista->cabeca;
    elemento = e->info;
    lista->cabeca = e->proximo;
    lista->tamanho--;
    free(e);

    return elemento;
}

void imprime_lista(ListaEncadeada *lista){
    if(lista->tamanho==0) printf("\nErro %i",ERRO_LISTA_VAZIA);
    else{ 
        Elemento *e = lista->cabeca;
        while(e!=NULL){
            printf("%i->",e->info);
            e=e->proximo;
        }
    }
    printf("\n");
}
