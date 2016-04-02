#include <stdio.h>
#include <string.h>

#define STR_T 100
#define P_T 100

int main(){
    char info[STR_T];
    char pais[P_T];
    FILE *arq;
    char url[] = "airlines.dat.txt";
    int c,i,j,teste=0;
    int br=0;

    arq = fopen(url,"r");
    if(arq==NULL){
        printf("erro ao ler o arquivo!\n");
        return 0;
    }
    
    while(fgets(info, STR_T, arq)!=NULL){
        c=0;
        teste++;
        for(i=0;i<STR_T;i++){
            if(info[i]==',')c++;
            if(c==6)break;
        }
        //printf("%i\n",i);
        i+=2;
        c=0;
        for(j=i;info[j]!='"';j++){
            pais[c++] = info[j];
        }
        pais[c]='\0';
        if(strcmp(pais,pais)==0){
            printf("Achou = %s\n",pais);
            br++;
        }
        //if(teste==4)return 0;
        //printf("%s\n",pais);
    }
    fclose(arq);
    return 0;
}

