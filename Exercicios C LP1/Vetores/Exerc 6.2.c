#include <stdio.h>

void preenche (int Arr[3][3], char L, char C){
    for (L=0;L<3;L++){
        for (C=0;C<3;C++){
            printf("Digite o valor da casa %hhd x %hhd: \n", L+1,C+1);
            scanf("%d", &Arr[L][C]);
        }
    }
}

float media (int Arr[3][3], char L, char C){

        int soma;
        for (L=0;L<3;L++){
            for (C=0;C<3;C++){
                soma += Arr[L][C];
            }
        }
    return soma/9;
}


int main (void){
    int arr[3][3];
    float med;
    char l,c;
    preenche(arr, l, c);
    med = media(arr,l,c);
    printf ("A média foi %f .\n",med);
    return 0;
}
