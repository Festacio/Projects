#include<stdio.h>

int main(void){
	int conta1,conta2;
	int* conta;
	char qtd;
	int* mais_saldo(int c1, int c2){
		int* M;
		if (c1>c2){
			M = &conta1;	
		} else {
			M = &conta2;
		}	
		return M;
	}
	void compra(int* C, int V[],int lim){
		char i;
		for (i=0; i= lim-1; i++) {
			printf("Insira o valor da compra: ");
			scanf("%d", &V[i] );			
			printf("%d\n",&V[i]);
			if (*C - V[i]>=0) {
				*C -= V[i];
				printf("Saldo atual: Conta 1: %d\n",conta1);
				printf("Saldo atual: Conta 2: %d\n",conta2);
				C = mais_saldo(conta1,conta2);	
			} else {
				print ("Saldo insuficiente para a compra.");
				i -= 1;
			}	
		}
	
	}
	
	printf("Insira o saldo da conta 1 e 2:");
	scanf("%d",&conta1);
	scanf("%d",&conta2);
	printf("Insira a quantidade de compras a serem feitas: ");
	scanf("%d", &qtd);
	int valor[qtd] ;
	conta = mais_saldo(conta1,conta2);	
	compra(conta, valor, qtd);
	return 0;
}


