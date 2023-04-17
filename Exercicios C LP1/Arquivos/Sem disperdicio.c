#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
struct Pessoa{
	int idade;
	char nome[51];
};

struct Pessoa preenche_pessoa(struct Pessoa p){
	printf("Insira a idade: ");
	scanf("%d", &p.idade);
	printf("Insira o nome: ");
	scanf("%s", p.nome);
	return p;
}

void escreva(FILE* f, struct Pessoa p){
	fwrite(&p.idade,sizeof(int),1,f);
	fwrite(p.nome,sizeof(char),strlen(p.nome)+1,f);
}

struct Pessoa ler(FILE* f){
	struct Pessoa p,paux;
	int i=0;
	fread(&p.idade,sizeof(int),1,f);
	fread(paux.nome,sizeof(char),1,f);
	while (paux.nome[0] != '\0'){
		p.nome[i]=paux.nome[0];
		i+=1;
		fread(paux.nome,sizeof(char),1,f);
	}
	return p;
}

void printar(struct Pessoa p){
	printf("Idade: %d\n",p.idade);
	printf("Nome: %s\n",p.nome);
}

int main (void){
	struct Pessoa p,p1;
	p = preenche_pessoa(p);
	FILE* f = fopen("C:/Users/Fernando Estácio/Desktop/ARQUIVOS UERJ/2° Semestre/LP1/C/Arquivos/abc.txt","w");
		escreva(f,p);
	fclose(f);
	
    fopen("C:/Users/Fernando Estácio/Desktop/ARQUIVOS UERJ/2° Semestre/LP1/C/Arquivos/abc.txt","r");
		p1=ler(f);
	fclose(f);
	
	printar(p1);
	return 0;
}
