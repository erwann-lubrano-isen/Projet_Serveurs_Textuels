#include <string.h>
#include "../headers/Salon.h"

int bd_Salon_check(unsigned long int idSalon, unsigned long int idServeur){
	FILE * fichier;
	fichier = fopen("rsc/salon.dat","r"); //ouverture de salon.dat
	if(fichier == NULL)return -1;		//test si fichier NULL
	Salon salon;	int i=0;
	while(fread(&salon,sizeof(Salon),1,fichier)!=EOF&&i<3){
		if(idSalon==salon.idSalon && idServeur==salon.idServeur){
			fclose(fichier);
			return 1;
		}++i;
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
	
	FILE * fichier;
	
	fichier = fopen("rsc/salon.dat","a");
	if(fichier == NULL)return 0;
	
	fwrite(&salon,sizeof(Salon),1,fichier);
	fclose(fichier);
	}	


