#include "headers/Membre.h"
#include "headers/Table.h"
#include <stdio.h>

int main(){
	printf("%d\n",bdd_getSize_table("membre"));
	printf("%d\n",bdd_check_membre(15,20));
	bdd_creer_membre(15,20);
	printf("%d\n",bdd_check_membre(15,20));
	return 0;
}