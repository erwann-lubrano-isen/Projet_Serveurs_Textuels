#ifndef __UTILISATEUR_H_
#define __UTILISATEUR_H_
#include "Serial.h"
#include "Table.h"
#include "Membre.h"
#include "Demande.h"
#include "Invitation.h"

typedef struct utilisateur {
	unsigned long int id;
	char pseudo[30];
	char motDePasse[30];
} Utilisateur;

void bdd_afficher_utilisateur();
int bdd_creer_utilisateur(char pseudo[], char motDePasse[]);
int bdd_supprimer_utilisateur(unsigned long int id);
unsigned long int bdd_getUtilisateur_id(const char * nom);
int bdd_getPseudo_utilisateur(char pseudo[], unsigned long int user_id);

#endif
