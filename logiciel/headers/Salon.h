#ifndef __SALON_H_
#define __UTILISATEUR_H_

typedef struct salon {
	unsigned long int idSalon;
	unsigned long int idServeur;
	char Nom[];
} Salon;

#endif
