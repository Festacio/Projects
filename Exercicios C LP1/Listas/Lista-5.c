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

void exibe(struct Caixa* L, int i){
	if (L == NULL){
		return;
	}else{
		printf("O valor da caixa %d e igual a %d\n",i,L->valor);
		exibe(L->prox,i+1);
	}
	
}

struct Caixa* Remove(struct Caixa* L, int i){
	struct caixa* aux;
	aux = busca(L,i);
	if (aux->prox != NULL){
		aux->prox = aux->prox->prox;
		return L;
	}else{
		L=NULL;	
		return L;
	}	
	
}

struct Caixa* busca(struct Caixa* L, int i){
	if (L == NULL){
		printf("O valor nao foi encontrado.");
		return NULL;
	}else{
		if (L->valor != i){
			struct caixa* aux = L;
			if (L->prox->valor == i);
				return L;
			else{
				busca(L->prox,i);
			}				
		}
		if (L->valor ==i){
			return L;
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
	printf("Insira o valor a ser removido da lista.\n");
	scanf("%d", &i);
	remove(L,i);
	exibe(L,i);
	return 0;
}
