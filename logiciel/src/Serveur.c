#include "../headers/Serveur.h"
#include "../headers/Serial.h"
#include "../headers/Table.h"

int bd_creationServeur(const char * const nom, unsigned long int idProprio) {

	Serveur serveur;
	strcpy(serveur.nom, nom);	//Initialisation de serveur 
	serveur.idProprio = idProprio;
	
	FILE *fichier;
	fichier = fopen("rsc/serveur.dat", "a"); //Ouverture de fichier
	if(fichier == NULL) return -1; //Vérification d'erreur
	
	serveur.id = incrementeSerial("serveur"); //Incrementation de serial
	
	fwrite(&serveur, sizeof(Serveur), 1, fichier);
	fclose(fichier);
	return 0;
}
