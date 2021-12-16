#include "../headers/ServeurMenu.h"

int menuServeur(unsigned long int idServ, unsigned long int idUtilisateur) {
	while (1) {
		char buffer[128];
		fgets(buffer, 127, stdin);
		int lenght = strlen(buffer);
		buffer[lenght-1]=' ';
		buffer[lenght]='\0';
			
			
		char *commande = strtok(buffer, " ");
		printf("\n%s\n", buffer);
		if(strcmp(commande, "!help") == 0) helpServeur();
		else if(strcmp(commande, "!invite") == 0) invitation(idServ);
		else if(strcmp(commande, "!accept") == 0) return 3;
		else if(strcmp(commande, "!create") == 0) return 4;
		else if(strcmp(commande, "!delete") == 0) return 5;
		else if((strcmp(commande, "!role") == 0 ));
		else if(strcmp(commande, "!perm") == 0 ) return 7;
		else if((strcmp(commande, "!back") == 0 )) return 1;
		else if((strcmp(commande, "!exit") == 0 )) return 0;
		else printf("%s: Action inexistante\n", commande);
	}
}

void helpServeur() {
	printf("!help :\n\tPermet d'afficher toutes les commandes de ce menu\n");
	printf("\n!invite \"pseudonyme\" :\n\tPermet d'inviter un utilisateur\n");
	printf("\n!accept \"pseudonyme\" :\n\tPermet d'accepter l'inviation d'un utilisateur\n");
	printf("\n!create \"nom de salon\" :\n\tPermet de créer un salon\n");
	printf("\n!delete \"nom du salon\" :\n\tPermet de détruire un salon\n");
	printf("\n!role \"pseudonyme\" \"nom du role\" :\n\tPermet d'affecter un membre à un rôle\n");
	printf("\n!perm \"nom de rôle\" \"permissions\" :\n\tPermet de créer un rôle\n");
	printf("\n!back :\n\tRetour à l'accueil\n");
	printf("\n!exit :\n\tQuitter\n");
}

int invitation(unsigned long int idServ) {
	char *pseudo = strtok(NULL, " "); 
	unsigned long int idU = bdd_getUtilisateur_id(pseudo);
	if (idU == 0) {
		printf("\n%s n'existe pas !\n", pseudo);
		return 0;		
	}
	
	bdd_creer_invitation(idU ,idServ);
	return 0;
}

/*int accept (unsigned long int idServ) {
	char *pseudo = strtok(NULL, " "); 
	unsigned long int idU = bdd_getUtilisateur_id(pseudo);
	
	if (idU == 0) {
		printf("\n%s n'existe pas !\n", pseudo);
		return 0;		
	}
	
	FILE *fichier = fopen("rsc/demande.dat", "r");
	Demande demande;
	
	int UtilisateurIntrouvable = 0;
	int AucuneDemande = 0;
	int i;
	
	for(i = 0; i < bdd_getSize_table("demande") && fread(&demande, sizeof(Demande), 1, fichier) != EOF; ++i) {
		if(demande.user_id == idU)
	
	
	}




}
*/


