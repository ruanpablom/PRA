#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#define STR_T 300
#define P_T 100

double cTime(struct timeval t1, struct timeval t2);

int main(){
    char info[STR_T];
    char pais[P_T];
    FILE *arq;
    char url[] = "airlines.dat.txt";
    int c,i,j,teste=0;
    int br=0;
    struct timeval t1, t2;
    double tLeitura=0;  

    arq = fopen(url,"r");
    if(arq==NULL){
        printf("erro ao ler o arquivo!\n");
        return 0;
    }
    gettimeofday(&t1, NULL);
    while(fgets(info, STR_T, arq)!=NULL){
        gettimeofday(&t2, NULL);
        tLeitura+=cTime(t1,t2);
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
            //printf("%s",info);
            br++;
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
