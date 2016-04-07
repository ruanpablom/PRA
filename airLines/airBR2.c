#include <stdio.h>
#include <string.h>

#define MAXBUFFER 8196
#define MAXL 1000
#define P_T 100
#define T_PB 6

int main(){
    char buffer[MAXBUFFER+1];
    char info[MAXL];
    char pais[T_PB+1];
    FILE *arq;
    char url[] = "airlines.dat.txt";
    int controle=0,c,i,j,teste=0,l,k,falta;
    int m,br=0,tam;

    arq = fopen(url,"r");
    if(arq==NULL){
        printf("erro ao ler o arquivo!\n");
        return 0;
    }

    falta=0;
    while(fread(buffer,sizeof(char),MAXBUFFER,arq)!=0){ 
        i=0;
        j=0;
        //printf("NewBuffer\n");
        while(1){
            m=0;
            buffer[MAXBUFFER+1]='\0'; 
            while(buffer[i++]!='\n'){
                m++;
                if(i==MAXBUFFER)break;
            } 
            if(falta)memcpy(&info[tam],&buffer[j],m);
            else memcpy(info,&buffer[j],m);
            //return 0;
            //if(falta)printf("%s\n teste\n",info);
            //memcpy(info,&buffer[j],m);
                info[m]='\0';
            if(i==MAXBUFFER){
                memcpy(info,&buffer[j],m);
                info[m]='\0';
                if(buffer[i]!='\n'){
                    falta=1;
                    tam = strlen(info);
                    //printf("%s\n teste\n %i\n",info,tam);
                } 
                break;
            }
            
            for(k=0;k<MAXL;k++){
                if(info[k]==',')c++;
                if(c==6)break;
            } 
            k+=2;
            c=0;    
            memcpy(pais,&info[k],sizeof(char)*T_PB);	

            if(strcmp(pais,"Brazil")==0){
                //printf("%s\n",info);
                br++;
            } 
            c=0;
            j=i;
            falta=0;
        }
    }

    fclose(arq);
    printf("Quantidade = %i\n",br);

    return 0;
}

