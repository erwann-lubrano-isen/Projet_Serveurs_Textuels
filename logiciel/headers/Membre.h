#ifndef __MEMBRE_H_
#define __MEMBRE_H_

#include <stdio.h>
#include <string.h>
#include "Table.h"
#include "Permissions_Serveur.h"
#include "Permissions_Salon.h"


/**
* @struct Membre
* @brief association Utilisateur-Serveur
*/
typedef struct Membre {
	unsigned long int idServeur;
	unsigned long int idUtilisateur;
	char role[30];
} Membre;


/**
* @brief crée un membre
* @param idServeur : id du serveur
* @param idUtilisateur : id de l'utilisateur
* @param role : role de l'utilisateur dans le serveur
*/
int bdd_creer_membre(unsigned long int idServeur, unsigned long idUtilisateur, const char * role);

/**
* @brief verifie si un membre existe
* @param idServeur : id du serveur
* @param idUtilisateur : id de l'utilisateur
* @return renvoie 1 si le membre existe sinon 0 
*/
int bdd_check_membre(unsigned long int idServeur, unsigned long idUtilisateur);

/**
* @brief supprime un membre
* @param idServeur : id du serveur
* @param idUtilisateur : id de l'utilisateur
*/
int bdd_supprimer_membre(unsigned long int idServeur, unsigned long idUtilisateur);

/**
*@brief affiche la liste des membres
*/
void bdd_afficher_membres();

/**
* @brief supprime tous les membres d'un serveur
* @param idServeur : id du serveur
*/
int supprimer_membres_serveur(unsigned long int idServeur);

/**
* @brief supprime tous les membres ayant un certain id d'utilisateur
* @param idUtilisateur : id de l'utilisateur
*/
int supprimer_membres_parId(unsigned long int id_user);

/**
* @brief change le role d'un membre
* @param idServeur : id du serveur
* @param idUtilisateur : id de l'utilisateur
*/
int role(unsigned long int userid, unsigned long int id_serveur);

#endif
