#include "../headers/MenuSalon.h"
#include <string.h>

int menuSalon() {
    char buffer[127];
    fgets(buffer, 127, stdin);
    char *commande = strtok(buffer, " ");
    if(!(strcmp(commande, "!help"))) return 1;
    if(!(strcmp(commande, "!perm"))) return 2;
    if(!(strcmp(commande, "!msg"))) return 3;
    if(!(strcmp(commande, "!exit"))) return 4;
    if(!(strcmp(commande, "!display"))) return 5;
    printf("%s: Action inexistante\n", commande);
    return -1;
}
void help(){
	printf("-------------Voici la liste des commandes--------------\n");
	printf("!perm rolename perm :  Change les droits pour le salon\n");
	printf("!msg : Envoyer un message\n");
	printf("!exit : Quitter le salon\n");
	printf("!display : Afficher tout les messages\n");
}

