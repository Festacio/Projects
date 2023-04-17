#include <stdio.h>
int main (void){    
    int a, b;
    int* p;
    printf("insira o valor de A e B: ");
    scanf(" %d", &a);
    printf("A = %d \n ", a);
    scanf(" %d", &b);
    printf("B = %d \n ", b);
    if (a>b){
        p = &a;
    }else{
        p = &b;
    }
    *p -= 50;    
    printf("A = %d \n", a);
    printf("B = %d \n", b);
    


}
