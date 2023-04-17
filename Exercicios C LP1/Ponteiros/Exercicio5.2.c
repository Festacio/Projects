#include <stdio.h>
int main (void){
		
	int conta1,conta2;
	int valor = 500;
	int* conta;

	int mais_saldo(int c1, int c2){
		int* M;
		if (c1>c2){
			M = &conta1;	
		} else {
			M = &conta2;
		}	
		return M;
	}
	void compra(int* C, int V){
		*C -= V;
		return 0;	
	}
	printf("Insira o saldo da conta 1 e 2:");
	scanf("%d",&conta1);
	scanf("%d",&conta2);
	conta = mais_saldo(conta1,conta2);
	compra(conta, valor);
	printf("Saldo atual: Conta 1: %d\n",conta1);
	printf("Saldo atual: Conta 2: %d\n",conta2);
	return 0;
}

