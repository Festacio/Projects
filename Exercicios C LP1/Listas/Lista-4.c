#include<stdio.h>
#include<stdlib.h>
 
struct Caixa{
	int valor;
	struct Caixa* prox;
};
	
void preenche_caixa(struct Caixa* L){
	if (L == NULL){
		return;		
	}else{
		scanf("%d", &L->valor);
		preenche_caixa(L->prox);
	}
	
}

char busca(struct Caixa* L, int i){
	if (L == NULL){
		printf("O valor nao foi encontrado.");
		return 0;
	}else{
		if (L->valor == i){
			printf("O valor foi encontrado.");
			return 1;
		}else{
			busca(L->prox,i);
		}
	}
	
}

int main (void){
	struct Caixa c1, c2, c3, c4, c5;
	struct Caixa* L;
	int i;
	L=&c1;
	c1.prox = &c2;
	c2.prox = &c3;
	c3.prox = &c4;
	c4.prox = &c5;
	c5.prox = NULL;
	preenche_caixa(L);
	printf("Insira o valor a ser buscado na lista.\n");
	scanf("%d", &i);
	char VF = busca(L,i);
	return 0;
}



	