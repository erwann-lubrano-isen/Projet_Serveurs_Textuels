#ifndef __SALON_H_
#define __UTILISATEUR_H_

#include "stdio.h"
#include "Table.h"
#include "Serial.h"

typedef struct salon {
	unsigned long int idSalon;
	unsigned long int idServeur;
	char Nom[];
}Salon;

int bd_Salon_check(unsigned long int idSalon, unsigned long int idServeur);
int bd_create_Salon(char Nom[], unsigned long int idServeur);

#endif
