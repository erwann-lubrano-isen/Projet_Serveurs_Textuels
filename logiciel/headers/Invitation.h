#ifndef __INVITATION_H_
#define __INVITATION_H_

#include <stdio.h>
#include "Table.h"

typedef struct Invitation{
	unsigned long int user_id;
	unsigned long int server_id;
}Invitation;

int bdd_creer_invitation(unsigned long int user_id, unsigned long int server_id);
void bdd_afficher_invitation();
int bdd_supprimer_invitation(unsigned long int user_id, unsigned long server_id);

#endif