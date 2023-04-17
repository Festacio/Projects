#include <stdio.h>

int Str_Len(char* STR){
	char i = 0;
	int soma=0;
		while (STR[i]!='\0'){
			soma +=1;
			i+=1;
	}
	return soma;
}


int main (void){
	int len;
	char str[100];
	printf("Escreva a string desejada: \n");
	scanf("%s", &str);
	len = Str_Len(str);
	printf("O tamanho da string digitada é: %d\n",len);
	return 0;
}
