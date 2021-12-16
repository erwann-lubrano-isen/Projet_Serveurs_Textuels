#ifndef __SALON_H_
#define __SALON_H_

#include "stdio.h"
#include "Table.h"
#include "Serial.h"

typedef struct salon {
	unsigned long int idSalon;
	unsigned long int idServeur;
	char nom[30];
}Salon;

int bdd_Salon_check(unsigned long int idSalon, unsigned long int idServeur);
int bdd_create_Salon(char nom[], unsigned long int idServeur);
void bdd_afficher_salon();
int bdd_supprimer_salon(unsigned long int idSalon, unsigned long idServeur);
int supprimer_salons_serveur(unsigned long int idServeur);
#endif
