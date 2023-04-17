#include<stdio.h>
#include<string.h>

struct Pessoa {
    int idade;
    char nome[51];
};

void escreve_arquivo(FILE* f, struct Pessoa* p){
    int i,j;
    for (i=0;i<3;i++){
        for (j=0;j<strlen((p+i)->nome) + 1;j++){
			fputc((p+j),f);
			
		}
    }
}

void preenche(struct Pessoa* p){
    int i;
    for (i=0;i<3;i++){
        printf("Digite a idade: ");
        scanf("%d",&p[i].idade);
        printf("Digite o nome: ");
        scanf("%s",p[i].nome);
    }
}

void ler_arquivo(FILE* f, struct Pessoa* p){
	int i=0;
	struct Pessoa p1[3];
	while (p1!= EOF){
		p1[i]=fgetc(f);
		i+=1;		
	}
	print_pessoa(p1);
}

void print_pessoa(struct Pessoa* p){
	int i;
	for (i=0;i<3;i++){
		printf("%s: %d\n",(p+i)->nome,(p+i)->idade);		
	}
}

int main(void){
	struct Pessoa p[10];
	preenche(p);
	FILE *f = fopen("C:/Users/Fernando Estácio/Desktop/ARQUIVOS UERJ/2° Semestre/LP1/C/Arquivos/chaach.txt", "w");
	escreve_arquivo(f,p);
	fclose(f);	
	f = fopen("C:/Users/Fernando Estácio/Desktop/ARQUIVOS UERJ/2° Semestre/LP1/C/Arquivos/chaach.txt", "r");
	ler_arquivo(f,p);
	fclose(f);
	return 0;
}
