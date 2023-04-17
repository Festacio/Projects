#include <stdio.h>

void preenche (int* x, int n){
	char i;
	for (i=0; i<n; i++) {
		printf("Digite o valor %hhd:", (i+1));
		scanf("%d", x+i);			
	}
}

float media (int* x, int n){
	char i;
	float soma;
	for (i=0; i<n; i++) {
		soma += *(x+i);			
	}
	return soma/n;
}

int main (void){
	int vet [100];
	int n;
	float Med;
	printf("Digite o valor de N ");
	scanf("%d", &n);
	preenche(vet, n);
	Med = media(vet, n);
	printf("A media dos valores do vetor e %f.\n", Med);
	return 0;
}	
