#ifndef __PERMISSIONS_SALON_H__
#define __PERMISSIONS_SALON_H__
#include <stdio.h>
#include <time.h>
#include "Table.h"
#include "Membre.h"
#include "Salon.h"
#include "Serveur.h"

typedef struct Permissions_Salon{
	unsigned long int id_salon;
	char Role[30];
	char perms[3];
}Permissions_Salon;

int insert_perm_salon(unsigned long int id_salon, char Role[], char perms[]);
void bdd_afficher_perm_salon();
int readPerm(unsigned long int id_salon, unsigned long int id_user);
int bdd_hasWPerm_salon(unsigned long int id_salon, unsigned long int id_user);
#endif
