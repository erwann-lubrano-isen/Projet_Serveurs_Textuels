
#ifndef __CONNEXION_H_
#define __CONNEXION_H_

#include <string.h>
#include <stdio.h>
#include "Serveur.h"
#include "Salon.h"
#include "Utilisateur.h"
#include "Invitation.h"
#include "Demande.h"
#include "Table.h"
#include "MenuSalon.h"
#include "Permissions_Serveur.h"
#include "Permissions_Salon.h"
#include "Acceuil_Actions.h"

/**
* @brief verifie si un role a deja des permissions sur un serveur
* @param id_serveur : id du serveur
* @param Role : nom du role
*/
int checkRoleServ(unsigned int long id_serveur, char Role[]);

/**
* @brief fonction principale du menu des serveurs
* @param idServ : id du serveur
* @param idUtilisateur : id de l'utilisateur
*/
int menuServeur(unsigned long int idServ, unsigned long int idUtilisateur);

/**
* @brief affiche les commandes possibles dans le menu des serveurs
* @param idServ : id du serveur
* @param idUtilisateur : id de l'utilisateur
*/
void helpServeur(unsigned long int idServ, unsigned long int idUtilisateur);

/**
* @brief invite un utilisateur à rejoindre le serveur
* @param idServ : id du serveur
*/
int invitation(unsigned long int idServ);

/**
* @brief commande pour créer un salon
* @param idServ : id du serveur
*/
int createSalon(unsigned long int idServ);

/**
* @brief commande pour supprimer un salon
* @param idServ : id du serveur
*/
int deleteSalon(unsigned long int idServ);

/**
* @brief verifie si un utilisateur a les droits d'administration sur un serveur 
* @param id_user : id de l'utilisateur
* @param id_serveur : id du serveur
*/
int isAdmin(unsigned long int id_user, unsigned long int id_serveur);

/**
* @brief affiche le prompt du menu des serveurs
* @param user_id : id de l'utilisateur connecté
* @param serveur_id : id du serveur
*/
void prompt_serveur(unsigned long int user_id, unsigned long int serveur_id);

/**
* @brief affiche la liste des salons disponibles
* @param idServ : id du serveur
* @param idUtilisateur : id de l'utilisateur
*/
void listeSalon(unsigned long int idServ, unsigned long int idUtilisateur);

/**
* @brief commande pour changer les permissions d'un role sur un serveur
* @param idServ : id du serveur
*/
int permServeur(unsigned long int idServ);

/**
* @brief commande pour afficher la liste des membre d'un serveur
* @param idServ : id du serveur
*/
int getMembres(unsigned long int idServ);

/**
* @brief recupère le nombre de salon associé au serveur
* @param idServ : id du serveur
* @return nombre de salon
*/
int getSalon(unsigned long int idServ);

/**
* @brief commande pour accepter la demande d'un utilisateur pour rejoindre le serveur
* @param idServ : id du serveur
*/
int accept(unsigned long int idServ);

/**
* @brief affiche les permissions en fonction des roles
* @param idServ : id du serveur
*/
void permMembres(unsigned long int idServ);

/**
* @brief commande pour changer le role d'un membre
* @param idServ : id du serveur
*/
int assignationRole(unsigned long int idServ);

/**
* @brief commande pour afficher la liste des membres
* @param idServ : id du serveur
*/
void listeMembres(unsigned long int idServ);

/**
* @brief commande pour afficher la liste des demandes
* @param idServ : id du serveur
*/
int list_demande(unsigned int long id_serveur);
#endif
