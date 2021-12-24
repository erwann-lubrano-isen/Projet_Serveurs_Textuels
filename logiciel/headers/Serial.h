#ifndef __SERIAL_H_
#define __SERIAL_H_
#include <string.h>
#include <stdio.h>

/**
* @struct Serial
* @brief compteur d'id 
*/
typedef struct Serial{
	char table_name[30];
	char attribute_name[30];
	unsigned long int count;
}Serial;

/**
* @brief incremente le compteur et renvoie l'id
* @param nomTable : nom de la table
* @return renvoie un nouvel id unique 
*/
unsigned long int incrementeSerial(char nomTable[]);
#endif
