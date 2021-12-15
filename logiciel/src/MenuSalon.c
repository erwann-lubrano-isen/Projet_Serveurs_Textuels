#include "../headers/MenuSalon.h"


int menuSalon() {
    char buffer[127];
    
    do{
    	fgets(buffer, 127, stdin);
    	char *commande = strtok(buffer, " ");
    	
    	if(!(strcmp(commande, "!help"))) helpSalon();
    	else if(!(strcmp(commande, "!perm"))) permSalon(id_salon);
    	else if(!(strcmp(commande, "!msg"))) msgSalon(id_salon);
    	else if(!(strcmp(commande, "!exit"))) return 0;
    	else if(!(strcmp(commande, "!back"))) return 1;
    	//else if(!(strcmp(commande, "!display"))) ;//display
    	else printf("%s: Action inexistante\n", commande);
    }while(1);    
    return 0;
}

void helpSalon(){
	printf("-------------Voici la liste des commandes--------------\n");
	printf("!perm rolename perm :  Change les droits pour le salon\n");
	printf("!msg text: Envoyer un message\n");
	printf("!exit : Quitter le programme\n");
	printf("!back : Retur en arrière\n");
	printf("!display : Afficher tout les messages\n");
}

int permSalon(unsigned long int id_salon){
	char *role = strtok(NULL, " ");
    	char *perm = strtok(NULL, " ");
    	if(strlen(role)>30 || strlen(perm)!=2 || perm[0]!='r' && perm[0]!='-' || perm[1]!='w' && perm[1]!='-'){
    		printf("Commande invalide");
    		return -1;
    	}
	insert_perm_salon(id_salon, role, perms);
	return 0; 
}

int msgSalon(unsigned long int id_salon){
	char *texte = strtok(NULL, " ");
	if (strlen(texte)>120){
		printf("Message trop long");
		return -1;
	}
	time_t date=time(NULL);
	bdd_creer_message(id_salon, id_utilisateur, date, texte);
	return 0;
}
