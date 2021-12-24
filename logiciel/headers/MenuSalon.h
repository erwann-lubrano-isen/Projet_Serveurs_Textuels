#ifndef __MENUSALON_H_
#define __MENUSALON_H_
#include <string.h>
#include <time.h>
#include "Permissions_Salon.h"
#include "Message.h"
#include "ServeurMenu.h"
#include "Membre.h"
#include "Salon.h"
#include "Serveur.h"
#include "Utilisateur.h"

/**
* @brief affiche les commandes faisables dans le menu des salons
* @param id_utilisateur : id de l'utilisateur connecté
* @param id_serveur : id du serveur dans lequel le salon se trouve
*/
void helpSalon(unsigned long int id_utilisateur, unsigned long int id_serveur);

/**
* @brief commande pour changer les permission d'un role sur un salon
* @param id_salon : id du salon
* @param id_serveur : id du serveur
*/
int permSalon(unsigned long int id_salon, unsigned long int id_serveur);

/**
* @brief commande pour envoyer un message
* @param id_salon : id du salon
* @param id_utilisateur : id de l'utilisateur qui envoie le message
*/
int msgSalon(unsigned long int id_salon, unsigned long int id_utilisateur);

/**
* @brief fonction principale du menu des salons
* @param id_salon : id du salon
* @param id_utilisateur : id de l'utilisateur connecté
* @param id_serveur : id du serveur dans lequel le salon se trouve
*/
int menuSalon(unsigned long int id_salon, unsigned long int id_utilisateur, unsigned long int id_serveur);

/**
* @brief verifie si un role existe ?
* @param id_user : id de l'utilisateur connecté
* @param id_salon : id du salon
* @param id_serveur : id du serveur dans lequel le salon se trouve
* @return 1:true 0:false
*/
int checkRole(unsigned long int id_user, unsigned long int id_salon, unsigned long int id_serveur);

/**
* @brief affiche les messages
* @param id_user : id de l'utilisateur connecté
* @param id_salon : id du salon
* @param id_serveur : id du serveur dans lequel le salon se trouve
*/
int displayMsg(unsigned long int id_utilisateur, unsigned long int id_serveur, unsigned long int id_salon);

/**
* @brief affiche le prompt du menu des salons
* @param id_user : id de l'utilisateur connecté
* @param id_salon : id du salon
* @param id_serveur : id du serveur dans lequel le salon se trouve
*/
void prompt_salon(unsigned long int user_id, unsigned long int serveur_id, unsigned long int idSalon);

/**
* @brief commande pour afficher les membres du salon et leurs permissions
* @param id_salon : id du salon
*/
void permMembresSalon(unsigned long int idSalon);
#endif
