#include <string.h>
#include "../headers/Permissions_Salon.h"
#include "../headers/Serial.h"

int insert_perm_salon(unsigned long int id_salon, char Role[], char perms[]){
	FILE * fichier;
	fichier = fopen("rsc/permission_salon.dat","r+"); //ouverture de salon.dat
	if(fichier == NULL)return -1;
	Permissions_Salon perm_salon;
	strcpy(perm_salon.Role, Role);
	strcpy(perm_salon.perms, perms);
	perm_salon.id_salon=id_salon;
	fseek(fichier, sizeof(Permissions_Salon)*(bdd_getSize_table("permission_salon")), SEEK_SET);
	fwrite(&perm_salon,sizeof(Permissions_Salon),1,fichier);
	fclose(fichier);
	bdd_increment_table("permission_salon");
	return 0;
}

void bdd_afficher_perm_salon(){
	int size = bdd_getSize_table("permission_salon");
	int i =0;
	Permissions_Salon permissions_Salon;
	FILE * file = NULL;
	file = fopen("rsc/permission_salon.dat","r");
	while(fread(&permissions_Salon,sizeof(Permissions_Salon),1,file) != EOF && i < size){
		printf("serv : %lu\tRole : %s\t%3s\n",permissions_Salon.id_salon,permissions_Salon.Role,permissions_Salon.perms);
		++i;
	}
	fclose(file);
}
