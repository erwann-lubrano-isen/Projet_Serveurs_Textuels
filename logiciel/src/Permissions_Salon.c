#include <string.h>
#include "../headers/Permissions_Salon.h"
#include "../headers/Serial.h"

int insert_perm_salon(unsigned long int id_salon, char Role[], char perms[]){
	FILE * fichier;
	fichier = fopen("rsc/permission_salon.dat","a"); //ouverture de salon.dat
	if(fichier == NULL)return -1;
	Permissions_Salon perm_salon;
	strcpy(perm_salon.Role, Role);
	strcpy(perm_salon.perms, perms);
	perm_salon.id_salon=id_salon;
	fclose(fichier);
	return 0;
}
