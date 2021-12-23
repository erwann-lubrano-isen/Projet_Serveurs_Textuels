#include <string.h>
#include "../headers/Salon.h"
#include "../headers/Serial.h"
#include "../headers/Table.h"

int bdd_Salon_check(unsigned long int idSalon, unsigned long int idServeur){
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

int bdd_create_Salon(char nom[], unsigned long int idServeur){
	Salon salon;
	strcpy(salon.nom, nom);
	salon.idServeur = idServeur;
	
	FILE * fichier;
	
	fichier = fopen("rsc/salon.dat","r+"); //ouverture de salon.dat
	if(fichier == NULL)return -1;
	salon.idSalon=incrementeSerial("salon");	//renvoie la taille de salon (en fct de incrementation ou decrementation, valeur change)
	insert_perm_salon(salon.idSalon, "Admin", "rw");
	insert_perm_salon(salon.idSalon, "Membre", "rw");
	
	fseek(fichier, sizeof(Salon)*(bdd_getSize_table("salon")), SEEK_SET);
	fwrite(&salon,sizeof(Salon),1,fichier); // ecriture du nouveau salon dans le fichier
	fclose(fichier);	
	bdd_increment_table("salon");
	return 0;
}
	
int bdd_supprimer_salon(unsigned long int idSalon, unsigned long idServeur){
	int size = bdd_getSize_table("salon");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("salon");
		return 0;
	}
	int i =0;
	Salon salon;
	Salon dernierSalon;
	FILE * file = NULL;
	file = fopen("rsc/salon.dat","r+");
	fseek(file,sizeof(Salon)*(size-1),SEEK_SET);
	fread(&dernierSalon,sizeof(Salon),1,file);
	fseek(file,0,SEEK_SET);
	while(fread(&salon,sizeof(Salon),1,file) != EOF && i < size){
		++i;
		if(salon.idSalon==idSalon && salon.idServeur==idServeur){
			fseek(file,-sizeof(Salon),SEEK_CUR);
			fwrite(&dernierSalon,sizeof(Salon),1,file);
			if(size>=1){
				bdd_decrement_table("salon");
				--size;
			}
			--i;
			fseek(file,sizeof(Salon)*(size-1),SEEK_SET);
			fread(&dernierSalon,sizeof(Salon),1,file);
			fseek(file,i*(sizeof(Salon)),SEEK_SET);
		}
		
	}
	fclose(file);
	return 0;
}

void bdd_afficher_salon(){
	int size = bdd_getSize_table("salon");
	int i =0;
	Salon salon;
	FILE * file = NULL;
	file = fopen("rsc/salon.dat","r");
	while(fread(&salon,sizeof(Salon),1,file) != EOF && i < size){
		printf("id_salon : %lu\tid_seveur:%lu\t%s\n",salon.idSalon,salon.idServeur,salon.nom);
		++i;
	}
	fclose(file);
}
	
int supprimer_salons_serveur(unsigned long int idServeur){
	int size = bdd_getSize_table("salon");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("salon");
		return 0;
	}
	int i =0;
	Salon salon;
	Salon dernierSalon;
	FILE * file = NULL;
	file = fopen("rsc/salon.dat","r+");
	fseek(file,sizeof(Salon)*(size-1),SEEK_SET);
	fread(&dernierSalon,sizeof(Salon),1,file);
	fseek(file,0,SEEK_SET);
	while(fread(&salon,sizeof(Salon),1,file) != EOF && i < size){
		++i;
		if(salon.idServeur==idServeur){
			fseek(file,-sizeof(Salon),SEEK_CUR);
			fwrite(&dernierSalon,sizeof(Salon),1,file);
			if(size>=1){
				bdd_decrement_table("salon");
				--size;
			}
			--i;
			fseek(file,sizeof(Salon)*(size-1),SEEK_SET);
			fread(&dernierSalon,sizeof(Salon),1,file);
			fseek(file,i*(sizeof(Salon)),SEEK_SET);
		}
		
	}
	fclose(file);
	return 0;
}
		
unsigned long int bdd_getSalon_id(unsigned long int id_serveur, const char * name){
	int size = bdd_getSize_table("salon");
	int i =0;
	Salon salon;
	FILE * file = NULL;
	file = fopen("rsc/salon.dat","r");
	while(fread(&salon, sizeof(Salon), 1, file) != EOF && i <= size){
		if(strcmp(salon.nom,name)==0 && salon.idServeur==id_serveur){
			fclose(file);
			return salon.idSalon;
		}
		++i;
	}
	fclose(file);
	return 0;
}

unsigned long int bdd_getServeur_id_by_salon_id(unsigned long int id_salon){
	int size = bdd_getSize_table("salon");
	int i =0;
	Salon salon;
	FILE * file = NULL;
	file = fopen("rsc/salon.dat","r");
	while(fread(&salon,sizeof(Salon),1,file) != EOF && i <= size){
		if(id_salon==salon.idSalon){
			fclose(file);
			return salon.idServeur;
		}
		++i;
	}
	fclose(file);
	return 0;
}
