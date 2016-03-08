//Equipe: Ruan Pablo, Bruna de Oliveira
//Lista adjacente

#ifndef LISTAENCADEADA_H
#define LISTAENCADEADA_H
//includes
//definição de constatntes
#define ERRO_LISTA_VAZIA -1
#define POSICAO_INEXISTENTE -2

//define estrutura eletemnto de lista
typedef struct elemento{
	int info;
	struct elemento *proximo;
}Elemento;

//define estrutura de cabeçalho da lista
typedef struct{
	int tamanho;
	Elemento *cabeca;
}ListaEncadeada;

//protótipo da funções
ListaEncadeada *criaLista();
int estah_vazia_listaenc(ListaEncadeada *lista);
void destroi_lista(ListaEncadeada *lista);
int adicionaNoInicio(ListaEncadeada *lista, int dados);
int adicionaNoFim(ListaEncadeada *lista, int dados);
void imprime_lista(ListaEncadeada *lista);

#endif
