#ifndef __PERMISSIONS_SALON_H__
#define __PERMISSIONS_SALON_H__

#include <stdio.h>
#include <time.h>

#include "Table.h"
#include "Membre.h"
#include "Salon.h"
#include "Serveur.h"

/**
* @struct Permissions_Salon
* @brief permissions d'un role sur un salon
*/
typedef struct Permissions_Salon{
	unsigned long int id_salon;
	char Role[30];
	char perms[3];
}Permissions_Salon;

/**
* @brief créer ou modifie les permissions d'un role sur un salon
* @param id_salon : id du salon
* @param Role : nom du role 
* @param perms : permissions à donner
*/
int insert_perm_salon(unsigned long int id_salon, char Role[], char perms[]);

/**
* @brief affiche toute la table permission_salon
*/
void bdd_afficher_perm_salon();

/**
* @brief verifie la permission de lecture d'un utilisateur sur un salon
* @param id_salon : id du salon
* @param id_user : id de l'utilisateur
* @return 1:true 0:false
*/
int readPerm(unsigned long int id_salon, unsigned long int id_user);

/**
* @brief verifie la permission d'écriture d'un utilisateur sur un salon
* @param id_salon : id du salon
* @param id_user : id de l'utilisateur
* @return 1:true 0:false
*/
int bdd_hasWPerm_salon(unsigned long int id_salon, unsigned long int id_user);

#endif
