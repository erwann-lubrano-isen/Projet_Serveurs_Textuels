#ifndef __UTILISATEUR_H_
#define __UTILISATEUR_H_

typedef struct utilisateur {
	unsigned long int id;
	char pseudo[];
	char motDePasse[];
} Utilisateur;

#endif
