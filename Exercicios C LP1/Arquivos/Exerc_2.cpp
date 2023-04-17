#include<stdio.h>
#include<string.h>
void ler (FILE* g){
    int a;
    a = fgetc(g);
	while(a!=EOF){
		printf("%d\n", a);
		a = fgetc(g);		
    }
}

int main (void){
    FILE* f = fopen("C:/Users/Fernando Estácio/Desktop/ARQUIVOS UERJ/2° Semestre/LP1/jooj.txt", "rb");							
    ler(f); 
    fclose(f);
    return 0;
}
