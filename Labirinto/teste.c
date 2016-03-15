#include<stdio.h>
#include"listaencadeada.h"
#include<stdlib.h>

int main(){
    ListaEncadeada **lista;
    //printf("%i\n",38%36);
    lista=(ListaEncadeada**)malloc(sizeof(ListaEncadeada*));
    lista[0]=criaLista();
    adicionaNoInicio(lista[0],2);
    imprime_lista(lista[0]);
    printf("\n");
    return 0;
}
