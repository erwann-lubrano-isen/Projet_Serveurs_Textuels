#include "headers/MenuSalon.h"
#include "headers/Serveur.h"
#include "headers/Salon.h"
#include "headers/Utilisateur.h"
#include "headers/Connexions_Action.h"

int main() {

	char Nom[30] = "Lilian";
	bdd_creer_utilisateur(Nom, Nom);
	char Nom2[30] = "Jean";
	bdd_creer_utilisateur(Nom2, Nom2);
	bd_creationServeur("LeServeur", 1);
	bdd_creer_invitation(2, 1);
	
    	return 0;
}
