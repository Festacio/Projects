#include<stdio.h>

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

void exibe(struct Caixa* L, int i){
	if (L == NULL){
		return;
	}else{
		printf("O valor da caixa %d e igual a %d\n",i,L->valor);
		exibe(L->prox,i+1);
	}
	
}

int main (void){
	struct Caixa c1, c2, c3, c4, c5;
	struct Caixa* L;
	int i = 1;
	L=&c1;
	c1.prox = &c2;
	c2.prox = &c3;
	c3.prox = &c4;
	c4.prox = &c5;
	c5.prox = NULL;
	preenche_caixa(L);
	exibe(L,i);
	c2.prox = &c4;
	L=&c3;
	c3.prox=&c1;
	exibe(L,i);
	return 0;
}
