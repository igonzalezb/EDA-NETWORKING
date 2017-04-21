#include <iostream>

#include "walkingAnimation.h"

int main()
{
	//CAT, EXPLOSION1, EXPLOSION2, HOMERDANCE, SUPERMARIO, SONIC, HEMAN, HULK, PICACHU, MICHAEL, INTRO
	
	printf("Seleccionar Animacion:\n\n");
	printf("\tA: Cat Running\n");
	printf("\tB: Explosion 1\n");
	printf("\tC: Explosion 2\n");
	printf("\tD: Homer Dance\n");
	printf("\tE: Super Mario\n");
	printf("\tF: Sonic\n");
	printf("\tG: HeMan\n");
	printf("\tH: Hulk\n");
	printf("\tI: Picachu\n");
	printf("\tJ: Michael Jackson\n");
	printf("\n\n\nPresione ENTER para salir...\n");
	
	
	char c = getchar();
	if (c == '\n')
	{
		return -1;
	}
	else if ((c >= 'k') || (c < 'a'))
	{
		printf("ERROR\n");
		return -1;
	}
	

	walkingAnimation intro('k');
	intro.startAnimation();
	walkingAnimation character(c);
	character.startAnimation();

	return 0;
}