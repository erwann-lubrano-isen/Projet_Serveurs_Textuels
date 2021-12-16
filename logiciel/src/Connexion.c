#include "../headers/Connexion.h"

int connexion() {
	char buffer[127];
	fgets(buffer, 127, stdin);
	char *commande = strtok(buffer, " ");
	if(!(strcmp(commande, "!help"))) helpConnexion();
	else if(!(strcmp(commande, "!login"))) login(buffer);
	else if(!(strcmp(commande, "!signup"))) signup(buffer);
	else if(!(strcmp(commande, "!exit"))) return 0;
	else printf("%s: Action inexistante\n", commande);
	return connexion();
}


