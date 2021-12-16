
#ifndef __CONNEXION_H_
#define __CONNEXION_H_

#include <string.h>
#include <stdio.h>
#include "Serveur.h"
#include "Utilisateur.h"
#include "Table.h"
#include "Invitation.h"

int menuServeur(unsigned long int idServ, unsigned long int idUtilisateur);
void helpServeur();
int invitation();

#endif
