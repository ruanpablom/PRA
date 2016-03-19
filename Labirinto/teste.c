#include<stdio.h>

int LIN = 8;
int COL = 37;

int main(){
    int n;
    printf("Digite o valor do elemento: ");
    scanf("%i",&n);
    printf("%i %i\n",(n-1)/COL,(n-1)%COL);
    return 0;
}
