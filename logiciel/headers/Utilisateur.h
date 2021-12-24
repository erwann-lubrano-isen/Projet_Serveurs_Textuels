#ifndef __UTILISATEUR_H_
#define __UTILISATEUR_H_
#include "Serial.h"
#include "Table.h"
#include "Membre.h"
#include "Demande.h"
#include "Invitation.h"

/**
* @struct Utilisateur
* @brief utilisateur
*/
typedef struct Utilisateur {
	unsigned long int id;
	char pseudo[30];
	char motDePasse[30];
} Utilisateur;

/**
* @brief affiche tous les utilisateurs
*/
void bdd_afficher_utilisateur();

/**
* @brief crée un compte utilisateur
* @param pseudo : nom de l'utilisateur
* @param motDePasse : mot de passe du compte
*/
int bdd_creer_utilisateur(char pseudo[], char motDePasse[]);

/**
* @brief supprime un compte utilisateur
* @param id : id de l'utilisateur
*/
int bdd_supprimer_utilisateur(unsigned long int id);

/**
* @brief renvoie l'id d'un utilisateur
* @param nom : pseudo de l'utilisateur
* @return renvoie 0 si l'utilisateur n'existe pas sinon renvoie son id
*/
unsigned long int bdd_getUtilisateur_id(const char * nom);

/**
* @brief "renvoie" le pseudo d'un utilisateur
* @param pseudo : pseudo de l'utilisateur
*/
int bdd_getPseudo_utilisateur(char pseudo[], unsigned long int user_id);

#endif
