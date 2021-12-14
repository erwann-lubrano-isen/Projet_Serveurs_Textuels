#ifndef __MEMBRE_H_
#define __UTILISATEUR_H_

typedef struct membre {
	unsigned long int IdServeur;
	unsigned long int idUtilisateur;
	char role[40];
} Membre;

#endif
