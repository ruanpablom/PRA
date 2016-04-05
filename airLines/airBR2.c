#include <stdio.h>
#include <string.h>

#define MAXBUFFER 100000
#define MAXL 1000
#define P_T 100

int main(){
    char buffer[MAXBUFFER+1];
    char info[MAXL];
    char pais[P_T];
    FILE *arq;
    char url[] = "airlines.dat.txt";
    int controle=0,c,i,j,teste=0,l,k,falta;
    int m,br=0;

    arq = fopen(url,"r");
    if(arq==NULL){
        printf("erro ao ler o arquivo!\n");
        return 0;
    }

    falta=0;
    while(fread(buffer,sizeof(char),MAXBUFFER,arq)!=0){ 
        i=0;
        while(1){
            buffer[MAXBUFFER+1]='\0';
            if(!falta){
                m=0;
            }

            falta=0;
            while(buffer[i++]!='\n'){
                //info[j++]=buffer[i++];
                //j
                m++;
                if(i==MAXBUFFER)break;
            } 
            //
            //return 0;
            if(i==MAXBUFFER){
                if(buffer[i]!='\n')falta=1;
                break;
            }
            strncpy(info,&buffer[j],sizeof(char)*i);
            //info[j]='\0';
            //printf("%s\n",info);
            //return 0;
            for(k=0;k<MAXL;k++){
                if(info[k]==',')c++;
                if(c==6)break;
            } 
            k+=2;
            c=0; 
            /*for(l=k;info[l]!='"';l++){
              pais[c++] = info[l];
              }*/
            l=k;
            m=0;
            while(info[l++]!='"'){
                //                   printf("teste\n");	
                m++;
            }    
            strncpy(pais,&info[k],sizeof(char)*m);	
            controle++;
            //return 0;
            //pais[m+1]='\0';
            printf("%s\n",pais);
            if(controle==3)return 0;
            if(strcmp(pais,"Brazil")==0){
                printf("%s\n",info);
                br++;
            }

            c=0;
        }
    }

    fclose(arq);
    printf("Quantidade = %i\n",br);

    return 0;
}

