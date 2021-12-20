#ifndef __ACCEUIL_ACTION_H__
#define __ACCEUIL_ACTION_H__

#include <stdio.h>
#include <string.h>
#include "Table.h"
#include "Serveur.h"
#include "Utilisateur.h"
#include "Demande.h"
#include "Invitation.h"
#include "Membre.h"
#include "ServeurMenu.h"

/**
* @brief fonction principale du menu d'accueil
* @param user_id : id de l'utilisateur connecté
* @return revoie 0 si le programme doit s'arreter (exit)
*/
int menu_Acceuil(unsigned long int user_id);

/**
* @brief commande qui supprime un serveur
* @param user_id : id de l'utilisateur connecté
* @return renvoie 0 en cas de succes
*/
int delete_serveur(unsigned long int user_id);

/**
* @brief commande pour creer une demande pour rejoindre un serveur
* @param user_id : id de l'utilisateur connecté
* @return 
*/
int join_serv(unsigned long int userid);

/**
* @brief commande pour creer un serveur
* @param user_id : id de l'utilisateur connecté
* @return 
*/
int create_serv(unsigned long int idProprio);

/**
* @brief commande pour afficher les commandes disponibles
*/
void help_acceuil();

/**
* @brief commande pour afficher les serveurs disponibles
* @param user_id : id de l'utilisateur connecté
* @return 
*/
int list_serv(unsigned int long user_id);

/**
* @brief commande pour afficher les invitations
* @param user_id : id de l'utilisateur connecté
* @return 
*/
int list_invit(unsigned int long user_id);

/**
* @brief commande pour aller dans un serveur
* @param user_id : id de l'utilisateur connecté
* @return 
*/
unsigned long int openServeur(unsigned int long user_id);

/**
* @brief commande pour ne plus etre membre d'un serveur
* @param user_id : id de l'utilisateur connecté
* @return 
*/
int quit_serv(unsigned long int userid);

/**
* @brief affiche le prompt dans le menu d'accueil
* @param user_id : id de l'utilisateur connecté
*/
void prompt_acceuil(unsigned long int user_id);
#endif
