#include "../headers/Membre.h"

int bdd_creer_membre(unsigned long int idServeur, unsigned long idUtilisateur){
	FILE * file = NULL;
	file = fopen("rsc/membre.dat","a");
	Membre membre;
	membre.idUtilisateur=idUtilisateur;
	membre.idServeur=idServeur;
	fwrite(&membre,sizeof(Membre),1,file);
	fclose(file);
	file = NULL;
	bdd_increment_table("membre");
}
		
		
int bdd_check_membre(unsigned long int idServeur, unsigned long idUtilisateur){
	Membre membre;
	FILE * file = NULL;
	file = fopen("rsc/membre.dat","r");
	while(fread(&membre,sizeof(Membre),1,file) != EOF){
		if(membre.idServeur==idServeur && membre.idUtilisateur==idUtilisateur){
			fclose(file);
			return 1;
		}
	}
	fclose(file);
	return 0;
}