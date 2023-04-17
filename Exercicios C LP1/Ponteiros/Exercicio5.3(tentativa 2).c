#include<stdio.h>

int main(void){
	int conta1,conta2;
	int* conta;
	int valor[5] = {100, 200, 300, 500, 1000};
	int* mais_saldo(int c1, int c2){
		int* M;
		if (c1>c2){
			M = &conta1;	
		} else {
			M = &conta2;
		}	
		return M;
	}
	void compra(int* C, int val[]){
		char i;
		for (i=0; i= 4; i++) {			
			if (*C - val[i]>=0) {
				*C -= val[i];
				printf("Saldo atual: Conta 1: %d\n",conta1);
				printf("Saldo atual: Conta 2: %d\n",conta2);
				C = mais_saldo(conta1,conta2);	
			} else {
				print ("Saldo insuficiente para a compra.");
				
			}	
		}
	}
	
	printf("Insira o saldo da conta 1 e 2:");
	scanf("%d",&conta1);
	scanf("%d",&conta2);
	conta = mais_saldo(conta1,conta2);
	compra(conta, valor);
	return 0;
}


