#include "../headers/Connexion.h"

int connexion() {
	char buffer[127];
	fgets(buffer, 127, stdin);
	char *commande = strtok(buffer, " ");
	if(!(strcmp(commande, "!help"))) return 1;
	if(!(strcmp(commande, "!login"))) return 2;
	if(!(strcmp(commande, "!signup"))) return 3;
	if(!(strcmp(commande, "!exit"))) return 0;
	printf("%s: Action inexistante\n", commande);
	return -1;
}
