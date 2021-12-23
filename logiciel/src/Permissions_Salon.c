#include <string.h>
#include "../headers/Permissions_Salon.h"
#include "../headers/Serial.h"

int insert_perm_salon(unsigned long int id_salon, char Role[], char perms[]){
	int size = bdd_getSize_table("permission_salon");
	int i =0;
	FILE * fichier;
	fichier = fopen("rsc/permission_salon.dat","r+"); //ouverture de salon.dat
	if(fichier == NULL)return -1;
	Permissions_Salon perm_salon;
	while(fread(&perm_salon,sizeof(Permissions_Salon),1,fichier) != EOF && i < size)
	{
		++i;
		if(strcmp(perm_salon.Role,Role)==0 && perm_salon.id_salon == id_salon){
		strcpy(perm_salon.perms,perms);
		fseek(fichier,-sizeof(Permissions_Salon),SEEK_CUR);  //on repositione le curseur juste avant
		fwrite(&perm_salon,sizeof(Permissions_Salon),1,fichier); //on ecrase le membre par nouveau
		printf("Changement de droits pour %s \n", Role);
		fclose(fichier);
		return 0;
		}
	}
	
	rewind(fichier);
	strcpy(perm_salon.Role, Role);
	strcpy(perm_salon.perms, perms);
	perm_salon.id_salon=id_salon;
	fseek(fichier, sizeof(Permissions_Salon)*(bdd_getSize_table("permission_salon")), SEEK_SET);
	fwrite(&perm_salon,sizeof(Permissions_Salon),1,fichier);
	fclose(fichier);
	bdd_increment_table("permission_salon");
	printf("Nouveau role : %s : permissions :  %s\n", Role, perms);
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

int readPerm(unsigned long int id_salon, unsigned long int id_user){
	char role[30];
	switch(bdd_getRole_membre(role,id_user,bdd_getServeur_id_by_salon_id(id_salon))){
		case -1:
			fprintf(stderr,"Erreur : Le fichier membre.dat n'a pas pu etre ouvert correctement\n");
			return -2;
		case 1:
			fprintf(stderr,"Erreur : membre inconnu\n");
			return 0;
	}
	int size = bdd_getSize_table("permission_salon");
	FILE * file = NULL;
	file = fopen("rsc/permission_salon.dat","r");
	Permissions_Salon permissions_Salon;
	if(file==NULL)return -1;
	for(int i = 0;i < size;++i){
		fread(&permissions_Salon,sizeof(Permissions_Salon),1,file);
		if(permissions_Salon.id_salon==id_salon && strcmp(permissions_Salon.Role,role)==0){
			fclose(file);
			return permissions_Salon.perms[0] == 'r';
		}
	}
	fclose(file);
	return 1;
}

int bdd_hasWPerm_salon(unsigned long int id_salon, unsigned long int id_user){
	char role[30];
	switch(bdd_getRole_membre(role,id_user,bdd_getServeur_id_by_salon_id(id_salon))){
		case -1:
			fprintf(stderr,"Erreur : Le fichier membre.dat n'a pas pu etre ouvert correctement\n");
			return -2;
		case 1:
			fprintf(stderr,"Erreur : membre inconnu\n");
			return 0;
	}
	int size = bdd_getSize_table("permission_salon");
	FILE * file = NULL;
	file = fopen("rsc/permission_salon.dat","r");
	Permissions_Salon permissions_Salon;
	if(file==NULL)return -1;
	for(int i = 0;i < size;++i){
		fread(&permissions_Salon,sizeof(Permissions_Salon),1,file);
		if(permissions_Salon.id_salon==id_salon && strcmp(permissions_Salon.Role,role)==0){
			fclose(file);
			return permissions_Salon.perms[1] == 'w';
		}
	}
	fclose(file);
	return 1;
}




