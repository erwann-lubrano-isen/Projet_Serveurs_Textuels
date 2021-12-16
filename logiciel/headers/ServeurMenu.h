#include <string.h>
#include <stdio.h>
#include "Serveur.h"
#include "Utilisateur.h"
#include "Invitation.h"
#include "Demande.h"
#ifndef __CONNEXION_H_
#define __CONNEXION_H_

int menuServeur(unsigned long int idServ, unsigned long int idUtilisateur);
void helpServeur();
int invitation();
int createSalon(unsigned long int idServ);
int deleteSalon(unsigned long int idServ);
int permServeur(unsigned long int id Serv, unsigned long int idUtilisateur);

#endif
