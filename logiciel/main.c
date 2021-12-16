#include "headers/MenuSalon.h"
#include "headers/Serveur.h"
#include "headers/Salon.h"
#include "headers/Utilisateur.h"

int main() {
	bdd_afficher_utilisateur();
	return menuServeur(1);
}
