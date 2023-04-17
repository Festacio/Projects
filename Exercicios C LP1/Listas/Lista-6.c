#include<stdio.h>
#include<stdlib.h>
 
struct Caixa{
	int valor;
	struct Caixa* prox;
};

void exibe(struct Caixa* L){
	if (L!=NULL){
		printf("%d\n",L->valor);
		exibe(L->prox);
	}else{
		return;
	}
	}
		
struct Caixa* insere(struct Caixa* L, int i){
	if (L==NULL){
		struct Caixa* C = malloc(sizeof(struct Caixa));
		C->valor = i;
		C->prox = NULL;
		return C;	
	}else{
		if(L->valor<i){
			L->prox=insere(L->prox,i);
			return L;
		}else{
			struct Caixa* C = malloc(sizeof(struct Caixa));
			C->prox = L->prox;
			C->valor = L->valor;
			L->prox = C;
			L->valor = i;
			return L;	
		}
	}
	
}

int main (void){
	struct Caixa* L = NULL;
	int i;
	scanf("%d",&i);
	while (i >= 0) {
		L=insere(L,i);
		scanf("%d",&i);
	}
	exibe (L);
	return 0;
}
