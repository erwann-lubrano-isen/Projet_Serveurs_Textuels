#ifndef __TABLE_H_
#define __TABLE_H_

#include <stdio.h>
#include <string.h>

/**
* @struct Table
* @brief contient le nombre de tuple d'une table
*/
typedef struct Table{
	char name[30];
	int size;
}Table;

/**
* @brief incremente le nombre de tuple de la table
* @param name : nom de la table
*/
int bdd_increment_table(const char * const name);

/**
* @brief decremente le nombre de tuple de la table
* @param name : nom de la table
*/
int bdd_decrement_table(const char * const name);

/**
* @brief permet de connaitre le nombre de tuple d'une table
* @param name : nom de la table
* @return renvoie le nombre de tuple
*/
int bdd_getSize_table(const char * const name);

#endif
