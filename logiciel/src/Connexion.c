#include "../headers/Connexion.h"

int connexion() {
	char buffer[127];
	fgets(buffer, 127, stdin);
	char *commande = strtok(buffer, " ");
	if(!(strcmp(commande, "!help"))) {
		helpConnexion();
		return 0;
	}
	
	if(!(strcmp(commande, "!login"))) return login(buffer);
	if(!(strcmp(commande, "!signup"))) return signup login(buffer);
	if(!(strcmp(commande, "!exit"))) return 0;
	printf("%s: Action inexistante\n", commande);
	return -1;
}

void helpConnexion() {
	printf("!help :\n\tPermet d'afficher toutes les commandes de ce menu");
	printf("\n!login \"pseudonyme\" \"mot de passe\" :\n\tPermet de se connecter");
	printf("\n!signup \"pseudonyme\" \"mot de passe\" :\n\tPermet de créer un compte");
	printf("\n!exit :\n\tQuitter");
}



