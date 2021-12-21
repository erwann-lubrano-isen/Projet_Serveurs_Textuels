#ifndef __INVITATION_H_
#define __INVITATION_H_

#include <stdio.h>
#include "Table.h"

/**
* @struct Invitation
* @brief invitation à rejoindre un serveur
*/
typedef struct Invitation{
	unsigned long int user_id;
	unsigned long int server_id;
}Invitation;

/**
* @brief cree une invitation
* @param user_id : id de l'utilisateur
* @param server_id : id du serveur
*/
int bdd_creer_invitation(unsigned long int user_id, unsigned long int server_id);

/**
* @brief affiche toutes les invitations
*/
void bdd_afficher_invitation();

/**
* @brief supprime une invitation
* @param user_id : id de l'utilisateur
* @param server_id : id du serveur
*/
int bdd_supprimer_invitation(unsigned long int user_id, unsigned long server_id);

/**
* @brief supprime toutes les invitations d'un utilisateur
* @param user_id : id de l'utilisateur
*/
int bdd_supprimer_invitation_parId(unsigned long int user_id);

#endif
