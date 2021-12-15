#include "../headers/Serveur.h"


int bd_creationServeur(const char * const nom, unsigned long int idProprio) {

	Serveur serveur;
	strcpy(serveur.nom, nom);	//Initialisation de serveur 
	serveur.idProprio = idProprio;
	serveur.id = incrementeSerial("serveur"); //Incrementation de serial
	
	FILE *fichier;
	fichier = fopen("rsc/serveur.dat", "r+"); //Ouverture de fichier
	if(fichier == NULL) return -1; //Vérification d'erreur
	
	
	fseek(fichier, sizeof(Serveur)*(bdd_getSize_table("serveur")), SEEK_SET);
	bdd_increment_table("serveur");
	fwrite(&serveur, sizeof(Serveur), 1, fichier);
	fclose(fichier);
	return 0;
}

int bd_suppressionServeur(unsigned long int id) {

	FILE *fichier = fopen("rsc/serveur.dat", "r+");
	if (fichier == NULL) return -1;
	
	Serveur serveur;
	
	for(int i = 1; i < bdd_getSize_table("serveur") && fread(&serveur, sizeof(Serveur), 1, fichier) != EOF; ++i) {
		if (serveur.id == id) {
			fseek(fichier, sizeof(Serveur)*(bdd_getSize_table("serveur")-1), SEEK_SET); //Positionnement du curseur au début de la dernière ligne
			fread(&serveur, sizeof(Serveur), 1, fichier);	//Obtention de la dernière ligne dans serveur
			fseek(fichier, sizeof(Serveur)*(i-1), SEEK_SET); //Positionnement au début de la ligne i
			fwrite(&serveur, sizeof(Serveur), 1, fichier);	//Ecriture de la dernière ligne contenue dans serveur
			bdd_decrement_table("serveur");
			return 0;
		}
	}
	fclose(fichier);	
}
/*
void bd_suppressionMembresEtServeur(unsigned long int id) {
	bd_suppressionServeur(id);
	supprimer_membres_serveur(id);
	supprimer_salons_serveur(id);
}*/
