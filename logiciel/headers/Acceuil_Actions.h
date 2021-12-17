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


int menu_Acceuil(unsigned long int user_id);
int delete_serveur(unsigned long int user_id);
int join_serv(unsigned long int userid);
//int join_serv(unsigned long int userid);
int create_serv(unsigned long int idProprio);
void help_acceuil();
int list_serv(unsigned int long user_id);
int list_invit(unsigned int long user_id);
unsigned long int openServeur(unsigned int long user_id);
int quit_serv(unsigned long int userid);
void prompt_acceuil(unsigned long int user_id);
#endif
