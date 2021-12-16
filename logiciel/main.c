#include "headers/MenuSalon.h"
#include "headers/Serveur.h"
#include "headers/Salon.h"
#include "headers/Utilisateur.h"
#include "headers/Connexions_Action.h"

int main() {
	char ps1[] = "Lilian";
	char ps2[] = "Napoléon";
	char ps3[] = "Jean";
	char ps4[] = "Louis";
	char ps5[] = "Philippe";
	char ps6[] = "Nicolas";
	char mdp[] = "mdp";
    	bdd_creer_utilisateur(ps1, mdp);
    	bdd_creer_utilisateur(ps2, mdp);
    	bdd_creer_utilisateur(ps3, mdp);
    	bdd_creer_utilisateur(ps4, mdp);
    	bdd_creer_utilisateur(ps5, mdp);
    	bdd_creer_utilisateur(ps6, mdp);
    	
    	bd_creationServeur("LeServeur", 1);
    	menuServeur(1, 1);
    	bdd_afficher_invitation();
    	return 0;
}
