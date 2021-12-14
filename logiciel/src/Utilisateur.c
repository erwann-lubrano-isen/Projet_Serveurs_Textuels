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
int bdd_supprimer_utilisateur(unsigned long int id){
	FILE * file = NULL;
	file = fopen("rsc/utilisateur.dat","a");
	

	//alors supprimer la "ligne" utilisateur
	//et remplace la derniere ligne par l'emplacement de la ligne supprimé
	
	fwrite(&utilisateur,sizeof(Utilisateur),1,file);
	fclose(file);
	
        bdd_decrement_table("utlisateur");
}
