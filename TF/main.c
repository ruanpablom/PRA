#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdint.h>

#define LIVRO 1
#define LEITOR 2
#define AUTOR 3
#define AUTOR_DO_LIVRO 4
#define EMPRESTIMO 5
#define HEXA_CODE 0xF0FA
#define ARQ_INEX -1
#define ARQ_NVAL -2
#define TAM_HEXA_CODE 7

int menu();
int incluirRegistro(int entidade);
char *stringEntidade(int entidade);

//strings globais
char banco[]        = {"biblioteca-"};
char livro[]        = {"Livro"};
char leitor[]       = {"Leitor"};
char autor[]        = {"Autor"};
char autorDoLivro[] = {"AutorDoLivro"};
char emprestimo[]   = {"Emprestimo"};

int main(){
    incluirRegistro(menu());		
    return 0;
}

int menu(){
    char *e;
    int entidade=0;	
    printf("1-Livro\n2-Leitor\n3-Autor\n4-Autor Do Livro\n5-Emprestimo\n");
    while(entidade<1 || entidade>5){
        printf("Digite o número da entidade que voce deseja operar : ");
        scanf("%i",&entidade);
        if(entidade<1 || entidade>5)printf("Digite uma entidade válida!\n");
    }
    system("clear");
    switch(entidade){
        case LIVRO:
            e = livro;
            break;
        case LEITOR:
            e = leitor;
            break;
        case AUTOR:
            e = autor;
            break;
        case AUTOR_DO_LIVRO:
            e = autorDoLivro;
            break;
        case EMPRESTIMO:
            e = emprestimo;
            break;
    }
    printf("Você selecionou a entidade \"%s\"\n",e);
    return entidade;
}

int incluirRegistro(int entidade){
    FILE *arq;
    char *bEntidade;
    int tEntidade;
    char hexC[TAM_HEXA_CODE];//variavel que receve a string com o valor hexadecimal
    uint32_t uv=0;//variavel que recebe o valor hexadecimal
    char *p;  
    int i;

    //nome do arquivo a ser analisado
    switch(entidade){
        case LIVRO:
            tEntidade = strlen(livro);
            break;
        case LEITOR:
            tEntidade = strlen(leitor);
            break;
        case AUTOR:
            tEntidade = strlen(autor);
            break;
        case AUTOR_DO_LIVRO:
            tEntidade = strlen(autorDoLivro);
            break;
        case EMPRESTIMO:
            tEntidade = strlen(livro);
            break;
    }
    bEntidade = (char*)malloc(sizeof(char)*strlen(banco)+sizeof(char)*tEntidade);
    if(bEntidade==NULL){
        printf("Memória Insuficiente!\n");
        exit(0);
    }
    memcpy(bEntidade,banco,sizeof(char)*strlen(banco));
    strcat(bEntidade,stringEntidade(entidade));
    //printf("%s\n",bEntidade);
    //nome do arquvio atribuido a string bEntidade

    //Abrir arquivo para inserção do registro
    arq=fopen(bEntidade,"ra");
    if(arq==NULL) return ARQ_INEX;
    fgets(hexC,sizeof(char)*TAM_HEXA_CODE,arq); 
    uv=strtoul(hexC, &p, 16);
    if(uv!=HEXA_CODE) return ARQ_NVAL;

}

char *stringEntidade(int entidade){
    switch(entidade){
        case LIVRO:
            return livro;
        case LEITOR:
            return leitor;
        case AUTOR:
            return autor;
        case AUTOR_DO_LIVRO:
            return autorDoLivro;
        case EMPRESTIMO:
            return emprestimo;
    }
}
