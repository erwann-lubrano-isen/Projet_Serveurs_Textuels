#include <string.h>
#include "../headers/Permissions_Serveur.h"
#include "../headers/Serial.h"

int insert_perm_serveur(unsigned long int id_serveur, unsigned long int User, char perms[]){
	FILE * fichier;
	fichier = fopen("rsc/permission_serveur.dat","a"); //ouverture de salon.dat
	if(fichier == NULL)return -1;
	Permissions_Serveur perm_serveur;
	strcpy(perm_serveur.perms, perms);
	perm_serveur.id_serveur=id_serveur;
	perm_serveur.User=User;
	fclose(fichier);
	bdd_increment_table("permission_serveur");
	return 0;
}

void bdd_afficher_perm_serveur(){
	int size = bdd_getSize_table("permission_serveur");
	int i =0;
	Permissions_Serveur permissions_Serveur;
	FILE * file = NULL;
	file = fopen("rsc/permission_serveur.dat","r");
	while(fread(&permissions_Serveur,sizeof(Permissions_Serveur),1,file) != EOF && i < size){
		printf("serv : %lu\tuser : %lu\t%3s\n",permissions_Serveur.id_serveur,permissions_Serveur.User,permissions_Serveur.perms);
		++i;
	}
	fclose(file);
}
