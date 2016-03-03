#include "labirinto.h"
#include <stdio.h>
#include <stdlib.h>

#define ERRO -1
#define COL 35
#define LIN 10

int main(){
	char lab[LIN][COL];
	char **labaux;
	labaux[0]=lab[0];
	labaux[1]=lab[1];
	labaux[2]=lab[2];
	labaux[3]=lab[3];
	labaux[4]=lab[4];
	labaux[5]=lab[5];
	labaux[6]=lab[6];
	labaux[7]=lab[7];
	labaux[8]=lab[8];
	labaux[9]=lab[9];
	carga("labirinto_test_1.txt", labaux);
	return 0;
}

int carga(char *nomeArquivo,char **lab){
   int i;
   FILE *arq = fopen(nomeArquivo,"r");
   if(arq==NULL){
   		printf("Falha ao ler o arquivo!\n");
   		return ERRO;
   }
   for(i=0;i<LIN;i++){
   		fgets(lab[i], COL*sizeof(char), arq);
   		printf("lab %s\n",lab[i]);
   }

   int num_linhas_lidas = 0;
   return num_linhas_lidas;
}
