#include<stdio.h>
#include<string.h>

void preenche (FILE* f,char* s){
	for (int i=0; i<strlen(s); i++){
		if (s[i]==95){
			fputc(32, f);
		}else{
			fputc(s[i],f);
		}			
    }
    fputc(10,f);
}

void string (FILE* f, char* s){
	int j;
	j=0;
	printf("Para botar espaco, insira '_' na string. \n");
	while (j!=10){
		scanf("%s", s);
		preenche(f,s);
		j+=1;
	}
}

int main (void){
    char s[26];
	FILE* f =  fopen("C:/Users/Fernando Estácio/Desktop/ARQUIVOS UERJ/2° Semestre/LP1/jooj.txt", "a");	
	string(f,s);
	fclose(f);
    return 0;
}
