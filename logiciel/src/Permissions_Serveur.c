#include <string.h>
#include "../headers/Permissions_Serveur.h"
#include "../headers/Serial.h"

int insert_perm_salon(unsigned long int id_serveur, unsigned long int User, char perms[]){
	FILE * fichier;
	fichier = fopen("rsc/permission_serveur.dat","a"); //ouverture de salon.dat
	if(fichier == NULL)return -1;
	Permissions_Serveur perm_serveur;
	strcpy(perm_serveur.perms, perms);
	perm_serveur.id_serveur=id_serveur;
	perm_serveur.User=User;
	fclose(fichier);
	return 0;
}
