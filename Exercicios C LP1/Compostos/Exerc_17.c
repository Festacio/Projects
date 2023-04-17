#include<stdio.h>

struct Classe{
	int sub;
	union Class{
		struct Barbaro{ //sub 0
			int vidaB, forca, agilB;
			char armaB[20];	
		}Barbaro;
		struct Mago{ //sub 1
			int vidaM, mana, intel;
			char armaM[20];
		}Mago;
		struct Arqueiro{ //sub 2 
			int vidaA, destreza, agilA;
			char armaA[20];
		}Arqueiro;
	}C;
};

void preenche(struct Classe* charac){

	switch (charac->sub){
		case 0:
			printf("Voce escolheu barbaro! Insira os atributos a seguir: \n");
			printf("HP: ");
			scanf("%d", &charac->C.Barbaro.vidaB);	
			printf("STR: ");
			scanf("%d",&charac->C.Barbaro.forca);
			printf("AGL: ");
			scanf("%d",&charac->C.Barbaro.agilB);
			printf("Qual a arma utilizada pelo barbaro? (maximo de 20 caracteres) \n");
			scanf("%s", &charac->C.Barbaro.armaB);
			break;
			
		case 1:
			printf("Tomanoteucu, mago é lixo demais. Insere essa merda logo, e somedaquimeo: \n");
			printf("HP: ");
			scanf("%d", &charac->C.Mago.vidaM);	
			printf("MP: ");
			scanf("%d",&charac->C.Mago.mana);
			printf("INT: ");
			scanf("%d",&charac->C.Mago.intel);
			printf("Qual a arma de pussy voce vai usar? (maximo de 20 caracteres) \n");
			scanf("%s", &charac->C.Mago.armaM);
			break;
		
		case 2:
			printf("Voce escolheu arqueiro! Insira os atributos a seguir: \n");
			printf("HP: ");
			scanf("%d", &charac->C.Arqueiro.vidaA);	
			printf("DES: ");
			scanf("%d",&charac->C.Arqueiro.destreza);
			printf("AGL: ");
			scanf("%d",&charac->C.Arqueiro.agilA);
			printf("Qual a arma utilizada pelo arqueiro? (maximo de 20 caracteres) \n");
			scanf("%s", &charac->C.Arqueiro.armaA);
			break;
			
		default:
			printf("Classe inexistente. \n");	
	}
} 

int main (void){
	struct Classe personagem;
	printf("Escolha sua classe: Barbaro[0], Mago[1], Arqueiro[2] \n");
	scanf("%d", &personagem.sub);
	preenche(&personagem); 
return 0;
}
