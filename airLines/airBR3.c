#include <stdio.h>
#include <string.h>

#define MAXBUFFER 8196
#define MAXL 1000
#define P_T 100

int main(){
    char buffer[MAXBUFFER+1];
    char info[MAXL];
    char pais[P_T];
    FILE *arq;
    char url[] = "airlines.dat.txt";
    int c,i,j,teste=0,l,k,falta;
    int br=0;

    arq = fopen(url,"r");
    if(arq==NULL){
        printf("erro ao ler o arquivo!\n");
        return 0;
    }

    falta=0;
    while(fread(buffer,sizeof(char),MAXBUFFER,arq)!=0){ 
        i=0;
        while(1){
            if(!falta)j=0;
            falta=0;
            while(buffer[i]!='\n'){
                info[j++]=buffer[i++];
                if(i==MAXBUFFER+1)break;
            }
            if(i==MAXBUFFER+1){
                if(buffer[i-1]!='\n')falta=1;
                break;
            }
            info[j]='\0';
            for(k=0;k<MAXL;k++){
                if(info[k]==',')c++;
                if(c==6)break;
            } 
            k+=2;
            c=0; 
            for(l=k;info[l]!='"';l++){
                pais[c++] = info[l];
            }

            pais[c]='\0';
            if(strcmp(pais,"Brazil")==0){
//                printf("%s\n",info);
                br++;
            } 
            i++;
            c=0;
        }
    }

    fclose(arq);
    printf("Quantidade = %i\n",br);

    return 0;
}
