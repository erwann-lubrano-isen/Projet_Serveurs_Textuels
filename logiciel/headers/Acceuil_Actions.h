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


/********************************************************************************
*	@brief menu_acceuil : permet  de donner acces a toute les commandes presente a cet endroit
*	
*	@param user_id : prend l'ID utilisateur necessaire pour la majoritée des commandes  
*	afin de cbler les actions d'un utilisateur précis (exemple : pour create_serveur, 	 
*		 quit_serveur, join_serveur,...)
*********************************************************************************/
int menu_Acceuil(unsigned long int user_id);
<<<<<<< HEAD

/********************************************************************************	
*	@brief delete_serveur : permet de supprimer un serveur si on en est le propriétaire
*
*	@param user_id : prend l'ID utilisateur afin de tester certaines conditions 	
*	   necessaire pour supprimer le serveur (ex : user_id = idProprio)
********************************************************************************/
int delete_serveur(char commande[], unsigned long int user_id);

/********************************************************************************	
*	@brief join_serv : permet de créer une demande pour rejoindre un serveur
*	
*	@param user_id : prend l'ID utilisateur afin de tester certaines conditions 	
*	   necessaire pour demander a rejoindre le serveur le serveur (ex : si l'utilisateur 
*       ne fait pas deja parti du serveur)
********************************************************************************/
int join_serv(unsigned long int userid);

/********************************************************************************	
*	@brief create_serv : permet de créer un serveur
*
*	@param user_id : prend l'ID utilisateur afin de tester certaines conditions 	*	   
	necessaire pour demander a rejoindre le serveur (ex : si deja exisant)
********************************************************************************/
int create_serv(unsigned long int idProprio);

/********************************************************************************	
*	@brief help_acceuil: affiche toute les commandes disponibles dans le menu acceuil
*
********************************************************************************/
void help_acceuil();
/********************************************************************************	
*	@brief list_serv : affiche la liste de serveur accesible a l'utilisateur
*
*	@param user_id : prend l'ID utilisateur afin de bien afficher uniquement les serveurs concernés par celui ci
********************************************************************************/
int list_serv(unsigned int long user_id);

/********************************************************************************	
*	@brief list_invit : affiche la liste d'invitation pour l'utilisateur
*
*	@param user_id : prend l'ID utilisateur afin de bien afficher uniquement les invitations concernés par celui ci
********************************************************************************/
int list_invit(unsigned int long user_id);

/********************************************************************************	
*	@brief openServeur : permet de rejoindre un serveur auquel on a deja acces
*
*	@param user_id : prend l'ID utilisateur pour savoir si il fait bien parti du serveur ciblé
********************************************************************************/
unsigned long int openServeur(unsigned int long user_id);

/********************************************************************************	
*	@brief quit_serv : permet de quitter un serveur
*
*	@param user_id : prend l'ID utilisateur afin de tester certaines conditions	  
	necessaire pour quitter le serveur (ex : si il en fait parti)
********************************************************************************/
int quit_serv(unsigned long int userid);

/********************************************************************************	
*	@brief prompt_acceuil : permet d'afficher le prompt de l'acceuil
*
*	@param user_id : prend l'ID utilisateur
********************************************************************************/
void prompt_acceuil(unsigned long int user_id);
#endif
