#ifndef __PERMISSIONS_SERVEUR_H__
#define __PERMISSIONS_SERVEUR_H__
#include <stdio.h>
#include <time.h>
#include "Table.h"

typedef struct Permissions_Serveur{
	unsigned long int id_serveur; //
	char Role[40]; //role du serveur
	char perms[3]; //WX
}Permissions_Serveur;

int insert_perm_serveur(unsigned long int id_serveur, unsigned long int User, char perms[]);
void bdd_afficher_perm_serveur();
	
#endif
