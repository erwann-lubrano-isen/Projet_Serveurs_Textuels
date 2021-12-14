#ifndef __SERIAL_H_
#define __SERIAL_H_
#include <string.h>
#include <stdio.h>


typedef struct Serial{
	char table_name[30];
	char attribute_name[30];
	unsigned long int count;
}Serial;

unsigned long int incrementeSerial(char nomTable[]);
#endif
