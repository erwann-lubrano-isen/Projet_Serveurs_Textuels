#include <string.h>
#include "../headers/Permissions_Serveur.h"
#include "../headers/Serial.h"

int insert_perm_serveur(unsigned long int id_serveur, char Role[], char perms[]){
	int size = bdd_getSize_table("permission_serveur");
	int i =0;	
	FILE * fichier;
	fichier = fopen("rsc/permission_serveur.dat","r+");
	if(fichier == NULL)return -1;
	Permissions_Serveur perm_serveur;
	while(fread(&perm_serveur,sizeof(Permissions_Serveur),1,fichier) != EOF && i < size)
	{
		++i;
		if(strcmp(perm_serveur.Role,Role)==0 && id_serveur == perm_serveur.id_serveur){
		strcpy(perm_serveur.perms,perms);
		fseek(fichier,-sizeof(Permissions_Serveur),SEEK_CUR);  //on repositione le curseur juste avant
		fwrite(&perm_serveur,sizeof(Permissions_Serveur),1,fichier); //on ecrase le membre par nouveau
		printf("\n\e[1;32mChangement de Permissions effectué \e[0m\n");
		printf("\n\e[3mNouvelles permissions\e[0m : \e[4m%s\e[0m \e[1m[%s]\e[0m\n\n", Role, perms);
		fclose(fichier);
		return 0;
		}
	}	
	
	rewind(fichier);
	strcpy(perm_serveur.perms, perms);
	strcpy(perm_serveur.Role,Role);
	perm_serveur.id_serveur=id_serveur;
	fseek(fichier, sizeof(Permissions_Serveur)*(bdd_getSize_table("permission_serveur")), SEEK_SET);
	fwrite(&perm_serveur,sizeof(Permissions_Serveur),1,fichier);
	fclose(fichier);
	bdd_increment_table("permission_serveur");
	printf("Nouveau role : %s : permissions :  %s\n", Role, perms);
	return 0;
}

void bdd_afficher_perm_serveur(){
	int size = bdd_getSize_table("permission_serveur");
	int i =0;
	Permissions_Serveur permissions_Serveur;
	FILE * file = NULL;
	file = fopen("rsc/permission_serveur.dat","r");
	while(fread(&permissions_Serveur,sizeof(Permissions_Serveur),1,file) != EOF && i < size){
		printf("serv : %lu\trole : %s\t%3s\n",permissions_Serveur.id_serveur,permissions_Serveur.Role,permissions_Serveur.perms);
		++i;
	}
	fclose(file);
}

int bdd_hasWPerm_serveur(unsigned long int serveur_id, unsigned long int user_id){
	char role[30];
	switch(bdd_getRole_membre(role,user_id,serveur_id)){
		case -1:
			fprintf(stderr,"Erreur : Le fichier membre.dat n'a pas pu etre ouvert correctement\n");
			return -2;
		case 1:
			fprintf(stderr,"Erreur : membre inconnu\n");
			return 0;
	}
	int size = bdd_getSize_table("permission_serveur");
	FILE * file = NULL;
	file = fopen("rsc/permission_serveur.dat","r");
	Permissions_Serveur permissions_Serveur;
	if(file==NULL)return -1;
	for(int i = 0;i < size;++i){
		fread(&permissions_Serveur,sizeof(Permissions_Serveur),1,file);
		if(permissions_Serveur.id_serveur==serveur_id && strcmp(permissions_Serveur.Role,role)==0){
			fclose(file);
			return permissions_Serveur.perms[0] == 'w' || bdd_getProprietaireServeur_id(serveur_id)==user_id;
		}
	}
	fclose(file);
	return bdd_getProprietaireServeur_id(serveur_id)==user_id;
}

int bdd_hasXPerm_serveur(unsigned long int serveur_id, unsigned long int user_id){
	char role[30];
	switch(bdd_getRole_membre(role,user_id,serveur_id)){
		case -1:
			fprintf(stderr,"Erreur : Le fichier membre.dat n'a pas pu etre ouvert correctement\n");
			return -2;
		case 1:
			fprintf(stderr,"Erreur : membre inconnu\n");
			return 0;
	}
	int size = bdd_getSize_table("permission_serveur");
	FILE * file = NULL;
	file = fopen("rsc/permission_serveur.dat","r");
	Permissions_Serveur permissions_Serveur;
	if(file==NULL)return -1;
	for(int i = 0;i < size;++i){
		fread(&permissions_Serveur,sizeof(Permissions_Serveur),1,file);
		if(permissions_Serveur.id_serveur==serveur_id && strcmp(permissions_Serveur.Role,role)==0){
			fclose(file);
			return permissions_Serveur.perms[1] == 'x';
		}
	}
	fclose(file);
	return bdd_getProprietaireServeur_id(serveur_id)==user_id;
}



