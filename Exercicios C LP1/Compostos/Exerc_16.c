#include <stdio.h>

union ponto{
	struct pon{
		float x,y,z;
	};
	float p[3];
};

int main (void){
	union ponto pt;
	printf("Insira as coordenadas x,y e z: \n");
	scanf("%f",&pt.x);
	scanf("%f",&pt.y);
	scanf("%f",&pt.z);
	printf("X: %f Y: %f Z: %f\n",pt.p[0],pt.p[1],pt.p[2]);
return 0;
}
