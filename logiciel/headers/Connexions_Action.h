#ifndef __CONNEXIONS_ACTION_H_
#define __CONNEXIONS_ACTION_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Utilisateur.h"
#include "Table.h"
#include "Acceuil_Actions.h"
#include "Serveur.h"

/**
* @brief commande pour afficher la liste des commandes
*/
void affich_help();

/**
* @brief fonction principale du menu de connexion
*/
int menuConnexion();

/**
* @brief commande pour creer un compte utilisateur
*/
int signup();

/**
* @brief commande pour se connecter à un compte utilisateur
* @return revoie l'id de l'utilisateur en cas de succes sinon renvoie 0
*/
unsigned long int  login();

/**
* @brief affiche le prompt du menu de connexion
*/
void connexion_prompt();

#endif

