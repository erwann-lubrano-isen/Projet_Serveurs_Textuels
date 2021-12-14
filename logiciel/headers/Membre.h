#ifndef __MEMBRE_H_
#define __UTILISATEUR_H_

#include <stdio.h>
#include <string.h>

#include "Table.h"

typedef struct Membre {
	unsigned long int idServeur;
	unsigned long int idUtilisateur;
	char role[40];
} Membre;



int bdd_creer_membre(unsigned long int idServeur, unsigned long idUtilisateur);
int bdd_check_membre(unsigned long int idServeur, unsigned long idUtilisateur);


#endif