#include <string.h>
#include <stdio.h>
#include "Serial.h"
#include "Table.h"
#ifndef __SERVEUR_H_
#define __UTILISATEUR_H_

typedef struct serveur {
	unsigned long int id;
	char nom[30];
	unsigned long int idProprio;
} Serveur;

#endif

int bd_creationServeur(const char *const nom, unsigned long int IdProprio);
int bd_suppressionServeur(const char *const nom);
void afficheServeur();
