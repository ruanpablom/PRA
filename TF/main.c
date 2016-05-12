#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define LIVRO 1
#define LEITOR 2
#define AUTOR 3
#define AUTOR_DO_LIVRO 4
#define EMPRESTIMO 5

int menu();
void incluirRegistro(int entidade);
char *stringEntidade(int entidade);

//strings globais
char banco[]        = {"biblioteca-"};
char livro[]        = {"livro"};
char leitor[]       = {"leitor"};
char autor[]        = {"autor"};
char autorDoLivro[] = {"autorDoLivro"};
char emprestimo[]   = {"emprestimo"};

int main(){
        incluirRegistro(menu());		
	return 0;
}

int menu(){
	int entidade=0;	
	printf("1-Livro\n2-Leitor\n3-Autor\n4-Autor Do Livro\n5-Emprestimo\n");
	while(entidade<1 || entidade>5){
		printf("Digite o número da entidade que voce deseja operar : ");
		scanf("%i",&entidade);
		if(entidade<1 || entidade>5)printf("Digite uma entidade válida!\n");
	}
	return entidade;
}

void incluirRegistro(int entidade){
    FILE *arq;
    char *bEntidade;
    int tEntidade;
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
    printf("%s\n",bEntidade);
    //parei aqui    
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
