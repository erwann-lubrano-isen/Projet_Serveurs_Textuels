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
		printf("Changement de droits pour %s \n", Role);
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
