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
	int size = bdd_getSize_table("membre");
	int i =0;
	Membre membre;
	FILE * file = NULL;
	file = fopen("rsc/membre.dat","r");
	while(fread(&membre,sizeof(Membre),1,file) != EOF && i <= size){
		if(membre.idServeur==idServeur && membre.idUtilisateur==idUtilisateur){
			fclose(file);
			return 1;
		}
		++i;
	}
	fclose(file);
	return 0;
}