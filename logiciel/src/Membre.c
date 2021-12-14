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

int bdd_supprimer_membre(unsigned long int idServeur, unsigned long idUtilisateur){
	int size = bdd_getSize_table("membre");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("membre");
		return 0;
	}
	int i =0;
	Membre membre;
	Membre dernierMembre;
	FILE * file = NULL;
	file = fopen("rsc/membre.dat","r+");
	fseek(file,sizeof(Membre)*(size-1),SEEK_SET);
	fread(&dernierMembre,sizeof(Membre),1,file);
	fseek(file,0,SEEK_SET);
	while(fread(&membre,sizeof(Membre),1,file) != EOF && i < size){
		++i;
		if(membre.idServeur==idServeur && membre.idUtilisateur==idUtilisateur){
			fseek(file,-sizeof(Membre),SEEK_CUR);
			fwrite(&dernierMembre,sizeof(Membre),1,file);
			if(size>=1){
				bdd_decrement_table("membre");
				--size;
			}
			--i;
			fseek(file,sizeof(Membre)*(size-1),SEEK_SET);
			fread(&dernierMembre,sizeof(Membre),1,file);
			fseek(file,i*(sizeof(Membre)),SEEK_SET);
		}
		
	}
	fclose(file);
	return 0;
}

void bdd_afficher_membres(){
	int size = bdd_getSize_table("membre");
	int i =0;
	Membre membre;
	FILE * file = NULL;
	file = fopen("rsc/membre.dat","r");
	while(fread(&membre,sizeof(Membre),1,file) != EOF && i < size){
		printf("id_serveur : %lu\tid_user: %lu\n",membre.idServeur,membre.idUtilisateur);
		++i;
	}
	fclose(file);
}