#include "../headers/Utilisateur.h"

int bdd_creer_utilisateur(char pseudo[], char motDePasse[]){
	FILE * file = NULL;
	file = fopen("rsc/utilisateur.dat","a");
	
	Utilisateur utilisateur;
	utilisateur.id=incrementSerial("utilisateur");
	strcpy(utilisateur.pseudo , pseudo);
	strcpy(utilisateur.motDePasse, motDePasse);
	
	fwrite(&utilisateur,sizeof(Utilisateur),1,file);
	fclose(file);
	
	bdd_increment_table("utilisateur");
}
s
