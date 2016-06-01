#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdint.h>

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

char cabBuffer[TAM_BUFFER];

int main(){
    //incluirRegistro(menu());		
    menu();
    return 0;
}

int menu(){
    char *e;
    char *bEntidade;
    int entidade=-1, opCode=-1;
    FILE *arq;
    char hexC[TAM_HEXA_CODE];//variavel que receve a string com o valor hexadecimal
    uint32_t uv=0;//variavel que recebe o valor hexadecimal
    char *p;

    printf("0-Sair\n1-Livro\n2-Leitor\n3-Autor\n4-Autor Do Livro\n5-Emprestimo\n");
    while(entidade<0 || entidade>5){
        printf("Digite o número da entidade que voce deseja operar : ");
        scanf("%i",&entidade);
        if(entidade<0 || entidade>5)printf("Digite uma entidade válida!\n");
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
        case 0:
            return 0;
    }
    
    printf("Você selecionou a entidade \"%s\"\n",e);
    
    //string do arquivo entidade
    bEntidade = (char*)malloc(sizeof(char)*strlen(banco)+sizeof(char)*strlen(e));
    if(bEntidade==NULL){
        printf("Memória Insuficiente!\n");
        exit(0);
    }
    memcpy(bEntidade,banco,sizeof(char)*strlen(banco));
    strcat(bEntidade,e);
    //printf("%s\n",bEntidade);
    
    //Abrir o arquivo verificando o hexaCode
    arq=fopen(bEntidade,"ra");
    if(arq==NULL) return ARQ_INEX;
    fgets(hexC,sizeof(char)*TAM_HEXA_CODE,arq); 
    uv=strtoul(hexC, &p, 16);
    if(uv!=HEXA_CODE) return ARQ_NVAL;
    //

    printf("Acesso válido!\n");
    
    printf("0-Sair\n1-Create\n2-Read\n3-Update\n4-Delete\n");
    
    while(opCode<0 || opCode>4){
        printf("Digite a operação você deseja realizar na entidade %s: ",e); 
        scanf("%i",&opCode);
        if(opCode<0 || opCode>4)printf("Digite uma operação válida!\n");
    }

    switch(opCode){
        case CREATE:
            criarRegistro(arq);
            break;
        case READ:
            break;
        case UPDATE:
            break;
        case DELETE:
            break;
    }

}

int criarRegistro(FILE *arq){
    int posBuffer=0;
    char *atrb[QTD_ATRIB];
    char palavra[TAM_PALAVRA];
    int tamPalavra=0;
    int qtdAtributos=0;
    int tamBuffer=0;
    while(1){
         fscanf(arq,"%c",&cabBuffer[tamBuffer]);
         if(cabBuffer[tamBuffer]=='%') break;
         tamBuffer++;
    } 
    //printf("%s\n",cabBuffer);
    posBuffer=0;
    while(posBuffer<tamBuffer){
        tamPalavra=0;
        while(cabBuffer[posBuffer]!=' ' && cabBuffer[posBuffer]!='\n'){
            palavra[tamPalavra] = cabBuffer[posBuffer];
            tamPalavra++;
            posBuffer++;
        }
        palavra[tamPalavra]='\0';
        printf("%s %i\n",palavra,tamPalavra);
    }
    return 0; 
}

