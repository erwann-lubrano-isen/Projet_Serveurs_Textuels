
#ifndef __CONNEXION_H_
#define __CONNEXION_H_

#include <string.h>
#include <stdio.h>
#include "Serveur.h"
#include "Utilisateur.h"
#include "Invitation.h"
#include "Demande.h"
#include "Table.h"
#include "MenuSalon.h"
#include "Permissions_Serveur.h"


int menuServeur(unsigned long int idServ, unsigned long int idUtilisateur);
void helpServeur();
int invitation();
int createSalon(unsigned long int idServ);
int deleteSalon(unsigned long int idServ);
int permServeur(unsigned long int id Serv, unsigned long int idUtilisateur);
int isAdmin(unsigned long int id_user,unsigned long int id_serveur);
void prompt_serveur(unsigned long int user_id, unsigned long int serveur_id);

#endif
