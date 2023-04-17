#include<stdio.h>
#include<string.h>

struct Pessoa {
    int idade;
    char nome[64];
    int peso;
};

void preenche(struct Pessoa* p){
    int i;
    for (i=0;i<3;i++){
        printf("Digite a idade: ");
        scanf("%d",&p[i].idade);
        printf("Digite o nome: ");
        scanf("%s",p[i].nome);
        printf("Digite o peso: ");
        scanf("%d",&p[i].peso);
    }
}
void escreve_arquivo(FILE* g, struct Pessoa* p){
	int i;
	for (i=0;i<3;i++){
		fwrite(p,sizeof(struct Pessoa),1,g);
		
	}
}

void ler_arquivo(FILE* g){
	fread(p,sizeof(struct Pessoa),1,g);
}

int main(void){
	struct Pessoa pessoa[3];
	preenche(pessoa);
	FILE* f = fopen("C:/Users/Fernando Estácio/Desktop/ARQUIVOS UERJ/2° Semestre/LP1/fuc.bin", "wb");	
	escreve_arquivo(f,pessoa);
	fclose(f);
	FILE* f = fopen("C:/Users/Fernando Estácio/Desktop/ARQUIVOS UERJ/2° Semestre/LP1/fuc.bin", "rb");
	ler_arquivo(f);	
	fclose(f);
	return 0;
}
