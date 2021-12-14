#include <string.h>
#include "../headers/Salon.h"
#include "../headers/Serial.h"


int bd_Salon_check(unsigned long int idSalon, unsigned long int idServeur){
	FILE * fichier;
	int size = bdd_getSize_table("salon");
	fichier = fopen("rsc/salon.dat","r"); //ouverture de salon.dat
	if(fichier == NULL)return -1;		//test si fichier NULL
	Salon salon;	
	int i=0;
	while(fread(&salon,sizeof(Salon),1,fichier)!=EOF&&i<size){
		if(idSalon==salon.idSalon && idServeur==salon.idServeur){
			fclose(fichier);
			return 1;
		}
		++i;
	}	//lecture jusqu'a la fin du fichier
	fclose(fichier);
	return  0;		//si aucune égalitée retrouvée, return 0
	//penser a serial
	}

int bd_create_Salon(char Nom[], unsigned long int idServeur){
	Salon salon;
	//bd_Salon_check(salon.idSalon, salon.idServeur)
	strcpy(salon.Nom, Nom);
	salon.idServeur = idServeur;
	salon.idSalon=1;
	
	FILE * fichier;
	
	fichier = fopen("rsc/salon.dat","a"); //ouverture de salon.dat
	if(fichier == NULL)return 0;
	idSalon=incrementeSerial("salon");	//renvoie la taille de salon (en fct de incrementation ou decrementation, valeur change)
	fwrite(&salon,sizeof(Salon),1,fichier); // ecriture du nouveau salon dans le fichier
	fclose(fichier);	
	bdd_increment_table("salon");

	}
	
	
	
		


