#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
    char **lab;
    int i,j;
    int **vertices;
    char c;
    FILE *arq;
    ListaEncadeada *caminho;

    if(argv[1]==NULL){
        printf("Erro! Arquivo de entrada inexistente.\n");
        printf("./labirinto \"arquivo de entrada\"\n");
        exit(0);
    }else nomeArquivo=argv[1];
    printf("%s\n",nomeArquivo);

    //Verifica a quantidade de linhas e colunas do arquivo
    arq = fopen(nomeArquivo,"r");
    if(arq==NULL){
        printf("Falha ao ler o arquivo!\n");
        return ERROARQ;
    }

    while((fscanf(arq,"%c",&c)) != EOF){
        if(c=='\n')LIN++;
        if(LIN==0)COL++;
        //printf("%c %i %i\n",c,LIN,COL); 
    }
    fclose(arq);
    //fim verificação

    //Aloca memória que será utilizada 
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
    //Fim alocação

    carga(lab, vertices);
    
    //imprime matriz de vertices
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            printf("%-3i ",vertices[i][j]);
        }
        printf("\n");
    }
    //fim da impressão
    
    //imprime a matriz do labirinto
    for(i=0;i<LIN;i++){
        for(j=0;j<COL;j++){
            printf("%c ",lab[i][j]);
        }
        printf("\n");
    }
    //fim da impressão da matriz labirinto

    caminho = caminhoMinimo(lab,vertices);
    imprime_lista(caminho);
    imprimeRatoLabirinto(lab,caminho);
    return 0;
}

void imprimeRatoLabirinto(char **lab, ListaEncadeada *caminho){
    int i,j;
    int pos,x,y;
    while(!estah_vazia_listaenc(caminho)){
        system("clear");
        for(i=0;i<LIN;i++){
            for(j=0;j<COL;j++){
                printf("%c",lab[i][j]);
            }
            printf("\n");
        }
        pos=removeElementoInicio(caminho);
        x=(pos-1)/COL;
        y=(pos-1)%COL;
        lab[x][y]='.';
        if(!estah_vazia_listaenc(caminho)){ 
            x=(caminho->cabeca->info-1)/COL;
            y=(caminho->cabeca->info-1)%COL;
            lab[x][y]='R';
        }
        sleep(1);

    }
}

ListaEncadeada *caminhoInicial(ListaEncadeada **mapa, int **vet, char **lab){
    ListaEncadeada *caminho;
    ListaEncadeada *pilha;
    ListaEncadeada *forkk;
    int tP,indice,inicio,saida,i;
    int qV=qtdVertices(vet);
    Elemento *elemento;
    int addPilha,qtdForkk;
    int tForkk;

    pilha = criaLista();
    caminho = criaLista();
    forkk = criaLista();

    inicio = posInicio(vet,lab);
    saida = posSaida(vet,lab);
    if(inicio==0 | saida==0)exit(0);

    adicionaNoInicio(pilha,inicio);
    while(1){
        addPilha=0;
        qtdForkk=0;
        tP = removeElementoInicio(pilha);
        //printf("Pilha = ");
        //imprime_lista(pilha); 
        indice = procuraNoMapa(mapa,tP,qV);
        elemento = mapa[indice]->cabeca;
        while(elemento!=NULL){
            if(!pertenceALista(pilha,elemento->info) && !pertenceALista(caminho,elemento->info) && elemento->info != tP){
                adicionaNoInicio(pilha,elemento->info);
                addPilha++;
            } 
            elemento = elemento->proximo;
        }
         if(tP==saida){
            adicionaNoFim(caminho,tP);
            break;
        }else if(addPilha>0){
            adicionaNoFim(caminho,tP);
            if(addPilha>1){
                for(i=0;i<addPilha-1;i++)adicionaNoInicio(forkk,tP);
            }
        }else if(forkk->tamanho>0){
            tForkk = removeElementoInicio(forkk);
            //printf("%i\n",)removeDoFimAte(caminho,tForkk);   
            removeDoFimAte(caminho,tForkk);
            //imprime_lista(caminho); 
        }
        
        if(estah_vazia_listaenc(pilha)){
            printf("NÃ£o existe Caminho\n");
            exit(0);
        } 
    } 
    //imprime_lista(caminho);
    return caminho;
}

int removeDoFimAte(ListaEncadeada *lista, int forkk){
    int elemento;
    Elemento *f;

    if(estah_vazia_listaenc(lista)){
        printf("Erro! NÃ£o hÃ¡ element na lista.\n ");
        //exit(0);
    }
    if(lista->tamanho==1)return removeElementoInicio(lista);
    Elemento *e = lista->cabeca;
    while(e->proximo!=NULL){
        e=e->proximo;
    }
    while(e->info!=forkk){
        e->anterior->proximo = NULL;
        f=e->anterior;
        free(e);
        e=f;
        lista->tamanho--;
    }
    elemento = e->info;

    return elemento;
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
    printf("Não existe lista onde %i é o cabeçaa\n",elemento);
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

int carga(char **lab, int **vertices){
    int i=0,j=0;
    int cont=1;
    FILE *arq = fopen(nomeArquivo,"r");
    if(arq==NULL){
        printf("Falha ao ler o arquivo!\n");
        return ERROARQ;
    }

    //printf("%i %i\n",LIN,COL);
    rewind(arq);
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
    if((x-1) < 0) return 0; 
    if(v[x-1][y]==INALCANCAVEL) return 0;
    else return v[x-1][y];
}

int pBaixo(int x, int y,  int **v){
    if((x+1) > LIN-1 | v[x+1][y]==INALCANCAVEL)return 0;
    if(v[x+1][y]==INALCANCAVEL)return 0;
    else return v[x+1][y];
}

int pDireita(int x, int y, int **v){
    if((y+1) > COL-1)return 0;
    if(v[x][y+1]==INALCANCAVEL)return 0;
    else return v[x][y+1];
}

int pEsquerda(int x, int y, int **v){
    if((y-1) < 0)return 0;
    if(v[x][y-1]==INALCANCAVEL)return 0;
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
        novo->anterior = NULL;
        if(novo->proximo!=NULL){
            novo->proximo->anterior = novo;
        }
        lista->cabeca = novo;
        lista->tamanho++;
        return lista->tamanho;
    }
    else return 0;
}

int adicionaNoFim(ListaEncadeada *lista, int dados){
    if(estah_vazia_listaenc(lista)==1){
        return adicionaNoInicio(lista,dados);
    }else{
        Elemento *e = lista->cabeca;
        while(e->proximo!=NULL){
            e = e->proximo;
        }
        Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
        if(novo!=NULL){
            novo->info = dados;
            novo->proximo = NULL;
            novo->anterior = e;
            e->proximo = novo;
            lista->tamanho++;
            return lista->tamanho;
        }
    }
    return 0;
}

int removeElementoInicio(ListaEncadeada *lista){
    int elemento;
    Elemento *e;

    if(estah_vazia_listaenc(lista)){
        printf("Erro! NÃo hÃ¡ elementos a lista.\n ");
        exit(0);
    }
    e = lista->cabeca;
    elemento = e->info;
    lista->cabeca = e->proximo; 
    if(e->proximo!=NULL)e->proximo->anterior = NULL;
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
