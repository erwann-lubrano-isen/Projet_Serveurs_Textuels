#ifndef __PERMISSIONS_SERVEUR_H__
#define __PERMISSIONS_SERVEUR_H__

#include <stdio.h>
#include <time.h>

#include "Table.h"
#include "Membre.h"
#include "Serveur.h"

/**
* @struct Permissions_Serveur
* @brief permissions d'un role sur un salon
*/
typedef struct Permissions_Serveur{
	unsigned long int id_serveur; //
	char Role[30]; //role du serveur
	char perms[3]; //WX
}Permissions_Serveur;


/**
* @brief créer ou modifie les permissions d'un role sur un serveur
* @param id_serveur : id du serveur
* @param Role : nom du role 
* @param perms : permissions à donner
*/
int insert_perm_serveur(unsigned long int id_serveur, char Role[], char perms[]);

/**
* @brief affiche toute la table permission_serveur
*/
void bdd_afficher_perm_serveur();

/**
* @brief verifie la permission d'écriture d'un utilisateur sur un serveur
* @param serveur_id : id du serveur
* @param user_id : id de l'utilisateur
* @return 1:true 0:false
*/
int bdd_hasWPerm_serveur(unsigned long int serveur_id, unsigned long int user_id);

/**
* @brief verifie la permission d'administration d'un utilisateur sur un serveur
* @param serveur_id : id du serveur
* @param user_id : id de l'utilisateur
* @return 1:true 0:false
*/
int bdd_hasXPerm_serveur(unsigned long int serveur_id, unsigned long int user_id);
	
#endif
