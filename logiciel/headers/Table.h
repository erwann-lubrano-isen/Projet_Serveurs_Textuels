#ifndef __TABLE_H_
#define __TABLE_H_

#include <stdio.h>

typedef struct Table{
	char name[30];
	int size;
}Table;


int bdd_increment_table(const char * const name);

#endif