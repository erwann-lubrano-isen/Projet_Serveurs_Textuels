#include "headers/Membre.h"
#include "headers/Table.h"
#include <stdio.h>

int main(){
	
	printf("%d\n",bdd_check_membre(15,20));
	bdd_supprimer_membre(15,20);
	printf("%d\n",bdd_check_membre(15,20));
	bdd_afficher_membres();
	printf("%d\n",bdd_getSize_table("membre"));
	
	return 0;
}