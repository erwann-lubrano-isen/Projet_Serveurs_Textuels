#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct Message{
	unsigned long int id_salon;
	unsigned long int id_utilisateur;
	time_t date;
	char texte[120];
}Message;

int bdd_creer_message(unsigned long int id_salon, unsigned long int id_utilisateur, time_t date, char texte[]);
	
#endif
