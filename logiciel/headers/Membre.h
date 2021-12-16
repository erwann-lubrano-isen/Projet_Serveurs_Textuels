#ifndef __MEMBRE_H_
#define __MEMBRE_H_

#include <stdio.h>
#include <string.h>
#include "Table.h"


typedef struct Membre {
	unsigned long int idServeur;
	unsigned long int idUtilisateur;
	char role[40];
} Membre;



int bdd_creer_membre(unsigned long int idServeur, unsigned long idUtilisateur, const char * role);
int bdd_check_membre(unsigned long int idServeur, unsigned long idUtilisateur);
int bdd_supprimer_membre(unsigned long int idServeur, unsigned long idUtilisateur);
void bdd_afficher_membres();
int supprimer_membres_serveur(unsigned long int idServeur);

#endif
