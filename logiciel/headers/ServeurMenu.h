
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

//int permServeur(unsigned long int idServ);
int checkRoleServ(unsigned int long id_serveur, char Role[]);
int menuServeur(unsigned long int idServ, unsigned long int idUtilisateur);
void helpServeur(unsigned long int idServ, unsigned long int idUtilisateur);
int invitation();
int createSalon(unsigned long int idServ);
int deleteSalon(unsigned long int idServ);
int isAdmin(unsigned long int id_user, unsigned long int id_serveur);
void prompt_serveur(unsigned long int user_id, unsigned long int serveur_id);
void listeSalon(unsigned long int idServ, unsigned long int idUtilisateur);
int permServeur(unsigned long int idServ);
int getMembres(unsigned long int idServ);
int getSalon(unsigned long int idServ);
int accept(unsigned long int idServ);
void permMembres(unsigned long int idServ);
int assignationRole(unsigned long int idServ);
void listeMembres(unsigned long int idServ);
int list_demande(unsigned int long id_serveur);
#endif
