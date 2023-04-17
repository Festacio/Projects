#include <stdio.h>

struct id{
	int sub; //sub 0,1,2
	union preco{
		float dolar; // sub 0
		float euro; // sub 1
		float real; // sub 2
	};
};

void exibe(struct id* Ident){
	switch(Ident->sub){
		case 0:
			printf("%f\n dólares\n", Ident);
			break;
		case 1:
			printf("%f\n euros\n", Ident);
			break;
		case 2:
			printf("%f\n reais\n", Ident);
			break;
		default:
			printf("Try again.");
			break;
	}
}
void altera(struct id* Ident, int* N_Sub){

		}
	}
}
int main (void){

return 0;
}
