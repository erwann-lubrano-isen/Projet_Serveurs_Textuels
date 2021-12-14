#ifndef __UTILISATEUR_H_
#define __UTILISATEUR_H_
#include "Serial.h"
#include "Table.h"

typedef struct utilisateur {
	unsigned long int id;
	char pseudo[];
	char motDePasse[];
} Utilisateur;

#endif
