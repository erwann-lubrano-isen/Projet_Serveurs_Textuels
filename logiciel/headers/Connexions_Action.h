#ifndef __CONNEXIONS_ACTION_H_
#define __CONNEXIONS_ACTION_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Utilisateur.h"

void affich_help();
int signup(char commande[]);
unsigned long int  login(char commande[]);

#endif