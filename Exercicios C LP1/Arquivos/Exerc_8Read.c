#include<stdio.h>
#include<stdlib.h>
 
struct Pessoa {
    int idade;
    char nome[51];
};

void ler_arquivo(FILE* f, struct Pessoa* p){
	int i;
	for (i=0; i<3; i++){
		fread((p+i), sizeof(int),1,f);
		fread((p+i), sizeof(char),strlen((p+i)->nome),f);
	}
}

void print_pessoa(struct Pessoa* p){
	int i;
	for (i=0;i<3;i++){
		printf("%s: %d\n",(p+i)->nome,(p+i)->idade);
	}
}

int main (void){
	struct Pessoa p[10];
	FILE* f = fopen("C:/Users/Fernando Estácio/Desktop/ARQUIVOS UERJ/2° Semestre/LP1/C/Arquivos/chaach.txt", "r");
	ler_arquivo(f,p);
	fclose(f);
	print_pessoa(p);
	return 0;
}	
	
