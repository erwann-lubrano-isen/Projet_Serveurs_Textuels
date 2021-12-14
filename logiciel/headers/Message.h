#ifndef __MESSAGE_H__
#define __MESSAGE_H__
#include <stdio.h>
#include <time.h>

typedef struct Message{
	unsigned long int id_salon;
	unsigned long int User;
	time_t Date[40];
	FICH * fichier;
}Message;
	
#endif
