#ifndef __ACCEUIL_ACTION_H__
#define __ACCEUIL_ACTION_H__

#include <stdio.h>
#include <string.h>
#include "Table.h"
#include "Serveur.h"
#include "Utilisateur.h"
#include "Demande.h"
#include "Invitation.h"

int menu_Acceuil(unsigned long int user_id);
int delete_serveur(char commande[], unsigned long int user_id);
int join_serv(unsigned long int userid);
//int delete_serveur(char commande[], unsigned long int user_id);
//int join_serv(unsigned long int userid);
int create_serv(unsigned long int idProprio);
void help_acceuil();
int list_serv(unsigned int long user_id);
int list_invit(unsigned int long user_id);
#endif
