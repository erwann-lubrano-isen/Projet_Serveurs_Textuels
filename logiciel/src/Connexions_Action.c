#include "../headers/Connexions_Action.h"

void helpConnexion() {
	printf("!help :\n\tPermet d'afficher toutes les commandes de ce menu");
	printf("\n!login \"pseudonyme\" \"mot de passe\" :\n\tPermet de se connecter");
	printf("\n!signup \"pseudonyme\" \"mot de passe\" :\n\tPermet de créer un compte");
	printf("\n!exit :\n\tQuitter");
}


int signup(char commande[]){
	char * pseudo=strtok(NULL," ");
	char * motdepasse=strtok(NULL," ");
	if(strlen(pseudo)>30 || strlen(motdepasse) > 30){
		printf("commande incorrecte\n");
		return 1;
	}
	FILE * fichier;
	Utilisateur utilisateur;
	fichier = fopen("rsc/utilisateur.dat","r");
	int size = bdd_getSize_table("utilisateur");
	int i=0;
	if(fichier == NULL)return -1;
	while(fread(&utilisateur,sizeof(Utilisateur),1,fichier)!=EOF&&i<size){
		if(strcmp(pseudo,utilisateur.pseudo)==0){
			fclose(fichier);
			printf("Ce pseudo est deja pris !\n");
			return 1;
		}
		++i;
	}
	fclose(fichier);
	bdd_creer_utilisateur(pseudo, motdepasse);
	return 0;
}

int login(char commande[]) {
	char * pseudo=strtok(NULL," ");
	char * motdepasse=strtok(NULL," ");
	if(strlen(pseudo)>30 || strlen(motdepasse) > 30){
		printf("commande incorrecte\n");
		return 1;
	}
	FILE * fichier;
	Utilisateur utilisateur;
	fichier = fopen("rsc/utilisateur.dat","r");
	int size = bdd_getSize_table("utilisateur");
	int i=0;
	if(fichier == NULL)return -1;
	while(fread(&utilisateur,sizeof(Utilisateur),1,fichier)!=EOF&&i<size){
		if(strcmp(pseudo,utilisateur.pseudo)==0){
			
			if(strcmp(motdepasse,utilisateur.motDePasse)==0){
				fclose(fichier);
				printf("Connecte !\n");
				return 0;
			}
			printf("Mot de passe incorrecte\n");
			fclose(fichier);
			return 1;
		}
		++i;
	}
	printf("utilisateur inexistant\n");
	fclose(fichier);
	bdd_creer_utilisateur(pseudo, motdepasse);
	return 1;
}


