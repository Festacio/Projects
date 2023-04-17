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
}

int main (void){
    char s[25];
    printf("Para botar espaço, insira '_' na string. \n")
    scanf("%s", s);
    FILE* f =  fopen("C:/Users/Fernando Estácio/Desktop/ARQUIVOS UERJ/2° Semestre/LP1/jooj.txt", "w");
    preenche(f, s);
    fclose(f);
    return 0;
}
