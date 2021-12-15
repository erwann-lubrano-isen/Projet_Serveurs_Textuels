#include "../headers/ServeurMenu.h"

int menuServeur() {
	char buffer[127];
	fgets(buffer, 127, stdin);
	char *commande = strtok(buffer, " ");
	if(!(strcmp(commande, "!help"))) return 1;
	if(!(strcmp(commande, "!invite"))) return 2;
	if(!(strcmp(commande, "!accept"))) return 3;
	if(!(strcmp(commande, "!create"))) return 4;
	if(!(strcmp(commande, "!delete"))) return 5;
	if(!(strcmp(commande, "!role"))) return 6;
	if(!(strcmp(commande, "!perm"))) return 7;
	if(!(strcmp(commande, "!back"))) return 8;
	if(!(strcmp(commande, "!exit"))) return 0;
	printf("%s: Action inexistante\n", commande);
	return -1;
}
