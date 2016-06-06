#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define MAXBUFFER 8192
#define MAXL 1000
#define P_T 100
#define T_PB 6

double cTime(struct timeval t1, struct timeval t2);

int main(){
    char buffer[MAXBUFFER+1];
    char info[MAXL];
    char pais[T_PB+1];
    FILE *arq;
    char url[] = "airlines.dat.txt";
    int controle=0,c,i,j,teste=0,l,k,falta;
    int m,br=0,tam;
    struct timeval t1, t2;
    double tLeitura=0;

    arq = fopen(url,"r");
    if(arq==NULL){
        printf("erro ao ler o arquivo!\n");
        return 0;
    }

    falta=0;
    gettimeofday(&t1, NULL);
    while(fread(buffer,sizeof(char),MAXBUFFER,arq)!=0){ 
        gettimeofday(&t2, NULL);
        tLeitura+=cTime(t1,t2);
        i=0;
        j=0;
        while(1){
            m=0;
            c=0; 
            buffer[MAXBUFFER+1]='\0'; 
            while(buffer[i++]!='\n'){
                m++;
                if(i==MAXBUFFER)break;
            } 
            if(falta){
                k=tam;
                while(m!=c){
                    info[k++]=buffer[j++];
                    c++;
                }
            }
            else{
                k=0;
                while(m!=c){
                    info[k++]=buffer[j++];
                    c++;
                }
            }
            if(falta){
                info[m+tam]='\0';
            }
            else{
                info[m]='\0';
            }
            if(i==MAXBUFFER){
                memcpy(info,&buffer[j],m);
                info[m]='\0';
                if(buffer[i]!='\n'){
                    falta=1;
                    tam = strlen(info); 
                } 
                break;
            }
            c=0;
            for(k=0;k<MAXL;k++){ 
                if(info[k]==',')c++;
                if(c==6)break;
            } 
            k+=2;    
            c=0;	
            for(c=0;c<T_PB;c++)pais[c]=info[k+c];
            pais[c]='\0';
            if(strcmp(pais,"Brazil")==0){ 
                br++;
            } 
            j=i;
            c=0;
            k=0;
            falta=0;
        }
        gettimeofday(&t1, NULL);
    }

    fclose(arq);
    printf("Quantidade = %i\n",br);
    printf("Tempo de Leitura = %g\n",tLeitura);
    return 0;
}

double cTime(struct timeval t1, struct timeval t2){
    double elapsedTime;

    elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
    elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
    elapsedTime /=1000.0;

    return elapsedTime;
}
