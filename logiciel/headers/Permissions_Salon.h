#ifndef __PERMISSIONS_SALON_H__
#define __PERMISSIONS_SALON_H__
#include <stdio.h>

typedef struct Permissions_Salon{
	unsigned long int id_salon;
	char Role[40];
	char perms[3];
}Permissions_Salon;
	
#endif
