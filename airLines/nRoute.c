#include<stdio.h>
#include<string.h>

#define L_T 90
#define C_Q 9
#define C_T 10

int main(){
    char src[] = "routes.dat.txt";
    char dest[] = "routes.dat";
    FILE *arq;
    char info[L_T];
    int i,j,k,anterior;
    int campo[C_Q];

    //Procura os maiores campos
    arq = fopen(src,"r");
    if(arq==NULL)return 0; 

    for(i=0;i<C_Q;i++)campo[i]=0;

    while(fgets(info,L_T,arq)!=NULL){
        j=0; 
        k=0;
        while(info[j]!='\n'){
            i=0;
            while(info[j]!=',' && info[j]!='\n'){
                i++;
                j++;
            }
            //printf("%c\n",info[j]);
            if(info[j+1]==','){
                campo[k++]=0;
                j++;
            }
            else if(campo[k]<i)campo[k++]=i;
            //printf("%c\n",info[j]);
        }
        //printf("%i %c\n",i,info[j]);

    }
    fclose(arq);
    for(i=0;i<C_Q;i++)printf("%i ",campo[i]);
    printf("\n");
    //Fim da procura pelos maiores campo
    return 0;
}
