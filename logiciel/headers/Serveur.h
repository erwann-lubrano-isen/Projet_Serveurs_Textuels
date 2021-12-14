#include <string.h>
#include <stdio.h>
#include "Serial.h"
#include "Table.h"
#include "Membre.h"
#include "Salon.h"
#ifndef __SERVEUR_H_
#define __UTILISATEUR_H_

typedef struct serveur {
	unsigned long int id;
	char nom[30];
	unsigned long int idProprio;
} Serveur;

#endif

int bd_creationServeur(const char *const nom, unsigned long int IdProprio);
int bd_suppressionServeur(unsigned long int id);
int bd_suppressionMembresEtServeur(unsigned long int id);
