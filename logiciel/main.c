#include "headers/MenuSalon.h"
#include "headers/Serveur.h"
#include "headers/Salon.h"
#include "headers/Utilisateur.h"

int main() {
	char test[30];
	char ss[30];
	printf("PSEUDO : ");
	scanf("%s", test);
	printf("\nMDP : ");
	scanf("%s", ss);
	printf("\n");
	bdd_creer_utilisateur(test, ss);
	bdd_afficher_utilisateur();
	bd_creationServeur("serveurdebg", 0);
	bdd_create_Salon("salondebg", 0);
	if (bdd_Salon_check(0, 0)==1){
		printf("Salon crée\n");
	}
	//bdd_afficher_salon();
    	menuSalon(0,0,0);
    	
	return 0;
}
