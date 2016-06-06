#include<stdio.h>
#include<string.h>

#define L_T 90
#define C_Q 9
#define C_T 10



int main(){
    char src[] = "routes.dat.txt";
    char dest[] = "routes.dat";
    FILE *arq,*arq2;
    char info[L_T];
    int i,j,k,anterior;
    int campo[C_Q];
    int fimLinha;
    int linha =0;

    //Procura os maiores campos
    arq = fopen(src,"r");
    if(arq==NULL)return 0; 

    for(i=0;i<C_Q;i++)campo[i]=0;

    while(fgets(info,L_T,arq)!=NULL){
        j=0; 
        k=0;
        fimLinha=0; 
        while(1){
            i=0;
            while(info[j]!=','){
                if(info[j]=='\n'){
                    fimLinha=1;
                    i--;
                    break;
                }
                i++;
                j++;
            } 
            if(!fimLinha)j++; 
            if(info[j]==','){
                k++;
                continue;
            }
            if(campo[k]<i)campo[k]=i;
            if(info[j]=='\n')break;
            k++;
        }
    }
    fclose(arq);
    for(i=0;i<C_Q;i++)printf("%i ",campo[i]);
    printf("\n");
    //return 0;
    //Fim da procura pelos maiores campo

    //Escrita do novo Arquivo com campos definidos
    arq = fopen(src,"r");
    if(arq==NULL)return 0;
    //deixa o arquivo em branco
    arq2 = fopen(dest,"w");
    if(arq==NULL)return 0;
    fclose(arq2);
    //fim arquivo em branco
    arq2 = fopen(dest,"a");
    if(arq==NULL)return 0;
    linha=0;
    while(fgets(info,L_T,arq)!=NULL){
        j=0;
        k=0;
        linha++; 
        while(k!=C_Q){
            i=campo[k];
            while(info[j]!=','){
                fprintf(arq2,"%c",info[j]);
                printf("%c",info[j]);
                j++;
                if(info[j]=='\n')break;
                i--; 
            }
            //printf("%i %i %i\n",i,campo[k],linha);
            //printf("%i\n",j);
            while(i!=0 && i>0 && k!=C_Q-1){
                fprintf(arq2," ");
                printf(" ");
                i--;
            }
            
            fprintf(arq2,"%c",info[j]);
            //if(info[j]=='\n')return 0;
            j++;
            k++;
        }
    }

    fclose(arq);
    fclose(arq2);
    return 0;
}
