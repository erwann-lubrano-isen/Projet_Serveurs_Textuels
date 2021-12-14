#include "headers/Salon.h"
#include "headers/Table.h"
#include "headers/Serial.h"
#include "headers/Demande.h"
#include <stdio.h>

int main(){

	bdd_stock_demande(4,5);
	//bdd_supprimer_demande(4,5);
	bdd_afficher_demande();
	
	return 0;
}
