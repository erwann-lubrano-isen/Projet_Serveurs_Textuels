#include "../headers/ServeurMenu.h"

int menuServeur() {
	char buffer[127];
	fgets(buffer, 127, stdin);
	char *commande = strtok(buffer, " ");
	if(!(strcmp(commande, "!help"))) helpServeur();
	else if(!(strcmp(commande, "!invite"))) return 2;
	else if(!(strcmp(commande, "!accept"))) return 3;
	else if(!(strcmp(commande, "!create"))) return 4;
	else if(!(strcmp(commande, "!delete"))) return 5;
	else if(!(strcmp(commande, "!role"))) return 6;
	else if(!(strcmp(commande, "!perm"))) return 7;
	else if(!(strcmp(commande, "!back"))) return 1;
	else if(!(strcmp(commande, "!exit"))) return 0;
	else printf("%s: Action inexistante\n", commande);
	return -1;
}

void helpServeur() {
	printf("!help :\n\tPermet d'afficher toutes les commandes de ce menu");
	printf("\n!invite \"pseudonyme\" :\n\tPermet d'inviter un utilisateur");
	printf("\n!accept \"pseudonyme\" :\n\tPermet d'accepter l'inviation d'un utilisateur");
	printf("\n!create \"nom de salon\" :\n\tPermet de créer un salon");
	printf("\n!delete \"nom du salon\" :\n\tPermet de détruire un salon");
	printf("\n!role \"pseudonyme\" \"nom du role\" :\n\tPermet d'affecter un membre à un rôle");
	printf("\n!perm \"nom de rôle\" \"permissions\" :\n\tPermet de créer un rôle");
	printf("\n!back :\n\tRetour à l'accueil");
	printf("\n!exit :\n\tQuitter");
}

int invitation() {
	char pseudo[30];
	char nomServeur[30];
	printf("Entrez le pseudonyme du destinataire :");
	scanf("%s", pseudo);
	printf("\nEntrez le nom du serveur :");
	scanf("%s", nomServeur);
	
	FILE *fichier = fopen("rsc/serveur.dat","r");
	
	if (fichier == NULL) {
	
	
	}
	Serveur serveur;
	for(int i = 0; fread(&serveur, sizeof(Serveur), 1, fichier) != EOF && i < bdd_getSize_table("serveur"); ++i) {	///!\ PREVOIR UTILISATEUR INTROUVABLE
		if(!(strcmp(serveur.nom, nomServeur))) break;
	}
	fclose(fichier);
	
	fichier = fopen("rsc/utilisateur.dat", "r");
	
	
	if (fichier == NULL) {
	
	
	}
	
	
	utilisateur utilisateur;
	for(int i = 0; fread(&utilisateur, sizeof(Utilisateur), 1, fichier) != EOF && i < bdd_getSize_table("utilisateur"); ++i) {
		if(!(strcmp(utilisateur.nom, pseudo))) break;
	}
	fclose(fichier);
	
	bdd_creer_invitation(utilisateur.id ,serveur.id)
	return 0;
}




