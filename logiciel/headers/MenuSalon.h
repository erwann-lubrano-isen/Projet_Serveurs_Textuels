#ifndef __MENUSALON_H_
#define __MENUSALON_H_
#include <string.h>
#include <time.h>
#include "Permissions_Salon.h"
#include "Message.h"
//#include "MenuServeur.h"

void helpSalon();
int permSalon(unsigned long int id_salon);
int msgSalon(unsigned long int id_salon, unsigned long int id_utilisateur);
int menuSalon(unsigned long int id_salon, unsigned long int id_utilisateur, unsigned long int id_serveur);
#endif
