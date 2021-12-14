#ifndef __PERMISSIONS_SERVEUR_H__
#define __PERMISSIONS_SERVEUR_H__
#include <stdio.h>
#include <time.h>

typedef struct Permissions_Serveur{
	unsigned long int id_serveur;
	unsigned long int User;
	char perms[3];
}Permissions_Serveur;
	
#endif
