#ifndef __ACCEUIL_ACTION_H__
#define __ACCEUIL_ACTION_H__

#include <stdio.h>
#include <string.h>
#include "Table.h"
#include "Serveur.h"

int menu_Acceuil(unsigned long int user_id);
int delete_serveur(char commande[], unsigned long int user_id);
#endif
