#include "../headers/MenuSalon.h"


int menuSalon(unsigned long int id_salon, unsigned long int id_utilisateur, unsigned long int id_serveur) {
    char buffer[128];
    do{
    	fgets(buffer, 127, stdin);
    	char *commande = strtok(buffer, " ");
    	
    	if(!(strcmp(commande, "help\n"))) helpSalon();
    	
    	else if(!(strcmp(commande, "perm"))&&isAdmin(id_utilisateur, id_serveur)) permSalon(id_salon);// if isAdmin(id_user, id_serveur)==1
    	else if(!(strcmp(commande, "msg"))) msgSalon(id_salon, id_utilisateur);
    	else if(!(strcmp(commande, "exit\n"))) return 0;
    	else if(!(strcmp(commande, "back\n"))) return 1;
    	//else if(!(strcmp(commande, "!display"))) ;//display
    	else printf("%s: Action inexistante\n", commande);
    }while(1);
}

void helpSalon(){
	printf("-------------Voici la liste des commandes--------------\n");
	printf("!perm rolename perm :  Change les droits pour le salon\n"); // if (isAdmin(id_user, id_serveur))
	printf("!msg text: Envoyer un message\n");
	printf("!exit : Quitter le programme\n");
	printf("!back : Retur en arrière\n");
	printf("!display : Afficher tout les messages\n");
}

int permSalon(unsigned long int id_salon){
	char *role = strtok(NULL, " ");
    	char *perm = strtok(NULL, "\n");
    	if(strlen(role)>30 || strlen(perm)!=2 || perm[0]!='r' && perm[0]!='-' || perm[1]!='w' && perm[1]!='-'){ //cas derreur
    		printf("Commande invalide\n");
    		return -1;
    	}
	insert_perm_salon(id_salon, role, perm); //appel de la fonction pour attribuer les role de chacun a un salon
	return 0;
}

int msgSalon(unsigned long int id_salon, unsigned long int id_utilisateur){
	char *texte = strtok(NULL, "\0");  // phrase envoyé par l'utilisateur, s'arrête au \n qui signifie le dernier caractere
	if (texte == NULL || strlen(texte)>120){ //cas d'érreur
		printf("Message invalide\n");
		return -1;
	}
	time_t date=time(NULL); // date = date actuel
	bdd_creer_message(id_salon, id_utilisateur, date, texte); //fonction de Message pour crée un message
	return 0;
}
