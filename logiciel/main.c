#include "headers/Membre.h"
#include "headers/Table.h"
#include "headers/Message.h"
#include <stdio.h>
#include <time.h>
#include <stdint.h>

int main(){
	
	printf("%d\n",bdd_check_membre(15,20));
	supprimer_membres_serveur(15);
	printf("%d\n",bdd_check_membre(15,20));
	bdd_afficher_membres();
	printf("%d\n",bdd_getSize_table("membre"));
	//bdd_creer_message(1, 1, time(NULL), "zefgizeucfhecfholeif\n");
	/*bdd_supprimer_message(1, 1, 1639493145);
	bdd_afficherMessages();*/
	return 0;
}