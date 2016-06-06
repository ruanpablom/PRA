#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdint.h>
#include "db.h"

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
    fseek(arq,1,SEEK_CUR);//posiciona o ponteiro de leitura do arquivo 1 caracter depois da posi��o atual 
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
    readHeader(arq);
    /*
    int posBuffer=0;
    char *atrb[QTD_ATRIB];
    int  attIni[QTD_ATRIB];
    int  tamAtt[QTD_ATRIB];
    char palavra[TAM_PALAVRA];
    int tamPalavra=0;
    int qtdAtributos=0;
    int tamBuffer=0;
    int qtd_lin=0;
    int attAtual = 0;
    char subPalavra[TAM_PALAVRA];
    char aux[TAM_PALAVRA];
    int i,j,tamSub,aux2,encTam;

    attIni[attAtual] = 0;//primeiro atributo inicia na posicao 0 do buffer
    while(1){//armazena o header no cabBuffer, o tamanho do cabBuffer na variavel tamBuffer, a quantidade de atributos na variavel qtdAtributos
        //a quantidade de linhas na variavel qtd_linhas.
        fscanf(arq,"%c",&cabBuffer[tamBuffer]);
        if(cabBuffer[tamBuffer]=='%') break;
        if(cabBuffer[tamBuffer]=='\n'){
            qtd_lin++;
            attIni[++attAtual] = tamBuffer+1;
            if(cabBuffer[attIni[attAtual-1]]=='\'') qtdAtributos++;
        }
        tamBuffer++;
    }
    attIni[attAtual+1]=tamBuffer;//para a ultima linha atribui 
    cabBuffer[tamBuffer+1]='\0';
    //int i=0;
      attAtual=1;
      while(cabBuffer[i]!='%'){
      while(i<=(attIni[attAtual]-2))printf("%c",cabBuffer[i++]);
      i=attIni[attAtual];
      attAtual++; 
      }*/
    /*
    for(i=0;i<qtdAtributos;i++){
        aux2=0;
        encTam=0;
        while(posBuffer<=attIni[i+1]){
            tamPalavra=0;
            while(1){
                while(cabBuffer[posBuffer]!=' ' && cabBuffer[posBuffer]!='\n'){
                    palavra[tamPalavra] = cabBuffer[posBuffer];
                    tamPalavra++;
                    if(posBuffer==tamBuffer)break;
                    posBuffer++;
                }
                palavra[tamPalavra]='\0';
                if(strcmp(palavra,"NOT")!=0 && strcmp(palavra,"default")!=0)break;
                if(cabBuffer[posBuffer]==' ')palavra[tamPalavra++]=' ';
                posBuffer++;
            }
            //descobrir o tamanho do campo do atributo
            if(!encTam){
                for(j=0;palavra[j]!='\0' && palavra[j]!='('; j++) subPalavra[j]=palavra[j];
                subPalavra[j]='\0';
                tamSub=j;
                if(strcmp(subPalavra,"int") == 0 || strcmp(subPalavra,"varchar") == 0 ){
                    for(j=tamSub+1;palavra[j]!=')';j++){
                        subPalavra[aux2++]=palavra[j];     
                    }
                    subPalavra[aux2]='\0';
                    tamAtt[i] = atoi(subPalavra);
                    encTam=1;
                }else if(strcmp(palavra,"date")==0){
                    tamAtt[i] = DATE;
                    encTam=1;
                }
            }
            //

            posBuffer++; 
            //printf("%s %s\n",palavra,subPalavra);
        }
        posBuffer = attIni[i+1]; 
    }
    //printf("%i %i\n",qtd_lin,qtdAtributos);
    //Lêpalavra por palavra
    
       while(posBuffer<=tamBuffer){
       tamPalavra=0;
       while(1){
       while(cabBuffer[posBuffer]!=' ' && cabBuffer[posBuffer]!='\n'){
       palavra[tamPalavra] = cabBuffer[posBuffer];
       tamPalavra++;
       if(posBuffer==tamBuffer)break;
       posBuffer++;
       }
       palavra[tamPalavra]='\0';
       if(strcmp(palavra,"NOT")!=0 && strcmp(palavra,"default")!=0 && strcmp(palavra,"PRIMARY")!=0)break;
       if(cabBuffer[posBuffer]==' ')palavra[tamPalavra++]=' ';
       posBuffer++;
       }
       printf("%s %i %i\n",palavra,posBuffer,tamBuffer);
       posBuffer++; 
       }*/
    
    return 0; 
}

Header readHeader(FILE *arq){
    int posBuffer=0;
    char *atrb[QTD_ATRIB];
    int  attIni[QTD_ATRIB];
    int  tamAtt[QTD_ATRIB];
    char palavra[TAM_PALAVRA];
    int tamPalavra=0;
    int qtdAtributos=0;
    int tamBuffer=0;
    int qtd_lin=0;
    int attAtual = 0;
    char subPalavra[TAM_PALAVRA];
    char aux[TAM_PALAVRA];
    int i,j,tamSub,aux2,encTam;
    Header header;
    
    header.qtdCampos=0;    
    attIni[attAtual] = 0;//primeiro atributo inicia na posicao 0 do buffer
    while(1){//armazena o header no cabBuffer, o tamanho do cabBuffer na variavel tamBuffer, a quantidade de atributos na variavel qtdAtributos
        //a quantidade de linhas na variavel qtd_linhas.
        fscanf(arq,"%c",&cabBuffer[tamBuffer]);
        if(cabBuffer[tamBuffer]=='%') break;
        if(cabBuffer[tamBuffer]=='\n'){
            qtd_lin++;
            attIni[++attAtual] = tamBuffer+1;
            if(cabBuffer[attIni[attAtual-1]]=='\'') header.qtdCampos++;
        }
        tamBuffer++;
    } 
    attIni[attAtual+1]=tamBuffer;//para a ultima linha atribui 
    cabBuffer[tamBuffer+1]='\0';
    header.nomeCampos = (char**)malloc(header.qtdCampos*sizeof(char*));
    header.autoIncrement = (int*)malloc(header.qtdCampos*sizeof(int));
    header.campoDefault = (int*)malloc(header.qtdCampos*sizeof(int));
    header.tamCampos = (int*)malloc(header.qtdCampos*sizeof(int));
    /*int i=0;
      attAtual=1;
      while(cabBuffer[i]!='%'){
      while(i<=(attIni[attAtual]-2))printf("%c",cabBuffer[i++]);
      i=attIni[attAtual];
      attAtual++; 
      }*/
    for(i=0;i<header.qtdCampos;i++){
        aux2=0;
        encTam=0;
        while(posBuffer<=attIni[i+1]){
            tamPalavra=0;
            while(1){
                while(cabBuffer[posBuffer]!=' ' && cabBuffer[posBuffer]!='\n'){
                    palavra[tamPalavra] = cabBuffer[posBuffer];
                    tamPalavra++;
                    if(posBuffer==tamBuffer)break;
                    posBuffer++;
                }
                palavra[tamPalavra]='\0';
                if(strcmp(palavra,"NOT")!=0 && strcmp(palavra,"default")!=0)break;
                if(cabBuffer[posBuffer]==' ')palavra[tamPalavra++]=' ';
                posBuffer++;
            }
            //descobrir o tamanho do campo do atributo
            if(!encTam){
                for(j=0;palavra[j]!='\0' && palavra[j]!='('; j++) subPalavra[j]=palavra[j];
                subPalavra[j]='\0';
                tamSub=j;
                if(strcmp(subPalavra,"int") == 0 || strcmp(subPalavra,"varchar") == 0 ){
                    for(j=tamSub+1;palavra[j]!=')';j++){
                        subPalavra[aux2++]=palavra[j];     
                    }
                    subPalavra[aux2]='\0';
                    tamAtt[i] = atoi(subPalavra);
                    encTam=1;
                }else if(strcmp(palavra,"date")==0){
                    tamAtt[i] = DATE;
                    encTam=1;
                }
            }
            

            posBuffer++; 
            //printf("%s %s\n",palavra,subPalavra);
        }
        posBuffer = attIni[i+1]; 
    }
    //printf("%i %i\n",qtd_lin,qtdAtributos);
    //Lêpalavra por palavra
    /*
       while(posBuffer<=tamBuffer){
       tamPalavra=0;
       while(1){
       while(cabBuffer[posBuffer]!=' ' && cabBuffer[posBuffer]!='\n'){
       palavra[tamPalavra] = cabBuffer[posBuffer];
       tamPalavra++;
       if(posBuffer==tamBuffer)break;
       posBuffer++;
       }
       palavra[tamPalavra]='\0';
       if(strcmp(palavra,"NOT")!=0 && strcmp(palavra,"default")!=0 && strcmp(palavra,"PRIMARY")!=0)break;
       if(cabBuffer[posBuffer]==' ')palavra[tamPalavra++]=' ';
       posBuffer++;
       }
       printf("%s %i %i\n",palavra,posBuffer,tamBuffer);
       posBuffer++; 
       }*/
    return header;
}
