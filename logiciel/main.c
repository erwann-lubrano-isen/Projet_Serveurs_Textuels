#include "headers/Salon.h"
#include "headers/Table.h"
#include "headers/Serial.h"
#include <stdio.h>

int main(){
	bdd_create_Salon("Chabala",20);
	bdd_create_Salon("KIKIKI",21);
	//printf("%d\n",bdd_Salon_check(15,20));
	//bdd_supprimer_salon(15,20);
	//printf("%d\n",bdd_Salon_check(15,20));
	bdd_afficher_salon();
	//printf("%d\n",bdd_getSize_table("salon"));
	
	return 0;
}
