#include <stdio.h>
#include <string.h>

#define MAXBUFFER 8196
#define MAXL 300
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

    /*while(fgets(info, STR_T, arq)!=NULL){
      c=0;
      teste++;
      for(i=0;i<STR_T;i++){
      if(info[i]==',')c++;
      if(c==6)break;
      }
      i+=2;
      c=0;
      for(j=i;info[j]!='"';j++){
      pais[c++] = info[j];
      }
      pais[c]='\0';
      if(strcmp(pais,"Brazil")==0){
      printf("%s\n",info);
      br++;
      }

      }*/
    //size_t newLen =  
    //vIdAtual=0;
    falta=0;
    while(fread(buffer,sizeof(char),MAXBUFFER,arq)!=0){ 
        i=0;
        while(1){
            buffer[MAXBUFFER]='\0';
            if(!falta)j=0;
            falta=0;
            
            while(buffer[i]!='\n'){
                info[j++]=buffer[i++];
                if(i==MAXBUFFER)break;
            }

            if(i==MAXBUFFER){
                if(buffer[i]!='\n')falta=1;
                break;
            }
            info[j]='\0';

            for(k=0;k<MAXL;i++){
                if(info[k]==',')c++;
                if(c==6)break;
            }
            k+=2;
            c=0;
printf("teste\n");
            for(l=k;info[l]!='"';l++){
                pais[c++] = info[l];
            }
            pais[c]='\0';
            if(strcmp(pais,"Brazil")==0){
                printf("%s\n",info);
                br++;
            }
        }
        //break;
    }
    /*while(size_t newLen = fread(info,sizeof(char),STR_T,arq)!=0){
      printf("teste\n");  
      }*/

    fclose(arq);
    printf("Quantidade = %i\n",br);

    return 0;
}

