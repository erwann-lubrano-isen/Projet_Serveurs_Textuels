#ifndef __SERVEUR_H_
#define __SERVEUR_H_
#include <string.h>
#include <stdio.h>
#include "Serial.h"
#include "Table.h"
#include "Membre.h"
#include "Salon.h"


typedef struct serveur {
	unsigned long int id;
	char nom[30];
	unsigned long int idProprio;
} Serveur;



int bd_creationServeur(const char *const nom, unsigned long int IdProprio);
int bd_suppressionServeur(unsigned long int id);
int bdd_supprimer_serveur_parId(unsigned long int user_id);
int bd_suppressionMembresEtServeur(unsigned long int id);
unsigned long int bdd_getServeur_id(const char * nom);
void bdd_afficher_serveurs();
unsigned long int bdd_getProprietaireServeur_id(unsigned long int serveur_id);


#endif

