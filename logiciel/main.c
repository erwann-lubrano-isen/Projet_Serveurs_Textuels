#include "headers/Membre.h"
#include "headers/Table.h"
#include "headers/Message.h"
#include "headers/Invitation.h"
#include <stdio.h>
#include <time.h>
#include <stdint.h>

int main(){
	
	/*printf("%d\n",bdd_check_membre(15,20));
	supprimer_membres_serveur(15);
	printf("%d\n",bdd_check_membre(15,20));
	bdd_afficher_membres();
	printf("%d\n",bdd_getSize_table("membre"));
	time_t date=time(NULL);
	bdd_creer_message(1, 1, date, "machin\n");
	bdd_afficherMessages();
	bdd_supprimer_message(1, 1, date);
	bdd_afficherMessages();*/
	
	bdd_creer_invitation(1,3);
	bdd_creer_invitation(5,6);
	
	bdd_supprimer_invitation(5,6);
	bdd_afficher_invitation();
	return 0;
}