#ifndef DB_H
#define DB_H

#define LIVRO 1
#define LEITOR 2
#define AUTOR 3
#define AUTOR_DO_LIVRO 4
#define EMPRESTIMO 5
#define CREATE 1
#define READ 2
#define UPDATE 3
#define DELETE 4
#define HEXA_CODE 0xF0FA
#define ARQ_INEX -1
#define ARQ_NVAL -2
#define TAM_HEXA_CODE 7
#define TAM_BUFFER 4096
#define QTD_ATRIB 100
#define TAM_PALAVRA 100
#define DATE 10
#define DEFAULT 1
#define NOT_N 2
#define N 3

typedef struct{
    int     qtdCampos;
    int     *tamCampos;
    char    **nomeCampos;
    int     *autoIncrement;
    int     *campoDefault;
}Header;

//strings globais
char banco[]        = {"biblioteca-"};
char livro[]        = {"Livro"};
char leitor[]       = {"Leitor"};
char autor[]        = {"Autor"};
char autorDoLivro[] = {"AutorDoLivro"};
char emprestimo[]   = {"Emprestimo"};
char cabBuffer[TAM_BUFFER];//buffer para o cabe√alho 

int menu();
int criarRegistro(FILE *arq);
Header readHeader(FILE *arq);

#endif
