//Equipe: Ruan Pablo, Bruna de Oliveira
//Lista adjacente

#include "listaencadeada.h"
#include <stdlib.h>
#include <stdio.h>

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

void imprime_lista(ListaEncadeada *lista){
		if(lista->tamanho==0) printf("\nErro %i",ERRO_LISTA_VAZIA);
		else{
			Elemento *e = lista->cabeca;
			while(e!=NULL){
				printf("%i->",e->info);
				e=e->proximo;
			}
		}
}
