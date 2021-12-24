#ifndef __SERVEUR_H_
#define __SERVEUR_H_
#include <string.h>
#include <stdio.h>
#include "Serial.h"
#include "Table.h"
#include "Membre.h"
#include "Salon.h"

/**
* @struct Serveur
* @brief Serveur
*/
typedef struct Serveur {
	unsigned long int id;
	char nom[30];
	unsigned long int idProprio;
} Serveur;


/**
* @brief crée un serveur
* @param nom : nom du serveur
* @param IdProprio : id du proprietaire du serveur
*/
int bd_creationServeur(const char *const nom, unsigned long int IdProprio);

/**
* @brief supprime un serveur
* @param id : id du serveur
*/
int bd_suppressionServeur(unsigned long int id);

/**
* @brief supprime tous les serveurs d'un utilisateur
* @param user_id : id de l'utilisateur
*/
int bdd_supprimer_serveur_parId(unsigned long int user_id);

/**
* @brief supprime un serveur et tous ses membres
* @param id : id du serveur
*/
int bd_suppressionMembresEtServeur(unsigned long int id);

/**
* @brief renvoie l'id d'un serveur
* @param nom : nom du serveur
* @return renvoie 0 si le serveur n'existe pas sinon renvoie son id
*/
unsigned long int bdd_getServeur_id(const char * nom);

/**
* @brief affiche tous les serveurs
*/
void bdd_afficher_serveurs();

/**
* @brief renvoie l'id du propriétaire d'un serveur
* @param serveur_id : id du serveur
* @return id du propriétaire
*/
unsigned long int bdd_getProprietaireServeur_id(unsigned long int serveur_id);


#endif

