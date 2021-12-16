#include <string.h>
#include "../headers/Demande.h"
#include "../headers/Serial.h"
#include "../headers/Table.h"

int bdd_stock_demande(unsigned long int user_id, unsigned long int server_id ){
	FILE * fichier;
	fichier = fopen("rsc/demande.dat","r+"); //ouverture de salon.dat
	if(fichier == NULL)return -1;
	Demande demande;
	demande.user_id=user_id;
	demande.server_id=server_id;
	fseek(fichier, sizeof(Demande)*(bdd_getSize_table("demande")), SEEK_SET);
	fwrite(&demande, sizeof(Demande), 1, fichier);
	fclose(fichier);
	//serveur.id = incrementeSerial("serveur"); //Incrementation de serial
	//fseek(fichier, sizeof(Serveur)*(bdd_getSize_table("serveur")), SEEK_SET);
	bdd_increment_table("demande");
	//fwrite(&serveur, sizeof(Serveur), 1, fichier);
	//fclose(fichier);
	return 0;
}

int bdd_supprimer_demande(unsigned long int user_id, unsigned long server_id){
	int size = bdd_getSize_table("demande");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("demande");
		return 0;
	}
	int i =0;
	Demande demande;
	Demande dernierDemande;
	FILE * file = NULL;
	file = fopen("rsc/demande.dat","r+");
	fseek(file,sizeof(Demande)*(size-1),SEEK_SET);
	fread(&dernierDemande,sizeof(Demande),1,file);
	fseek(file,0,SEEK_SET);
	while(fread(&demande,sizeof(Demande),1,file) != EOF && i < size){
		++i;
		if(demande.user_id==user_id && demande.server_id==server_id){
			fseek(file,-sizeof(Demande),SEEK_CUR);
			fwrite(&dernierDemande,sizeof(Demande),1,file);
			if(size>=1){
				bdd_decrement_table("demande");
				--size;
			}
			--i;
			fseek(file,sizeof(Demande)*(size-1),SEEK_SET);
			fread(&dernierDemande,sizeof(Demande),1,file);
			fseek(file,i*(sizeof(Demande)),SEEK_SET);
		}
		
	}
	fclose(file);
	return 0;
}
int bdd_supprimer_demande_parId(unsigned long int user_id){
	int size = bdd_getSize_table("demande");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("demande");
		return 0;
	}
	int i =0;
	Demande demande;
	Demande dernierDemande;
	FILE * file = NULL;
	file = fopen("rsc/demande.dat","r+");
	fseek(file,sizeof(Demande)*(size-1),SEEK_SET);
	fread(&dernierDemande,sizeof(Demande),1,file);
	fseek(file,0,SEEK_SET);
	while(fread(&demande,sizeof(Demande),1,file) != EOF && i < size){
		++i;
		if(demande.user_id==user_id){
			fseek(file,-sizeof(Demande),SEEK_CUR);
			fwrite(&dernierDemande,sizeof(Demande),1,file);
			if(size>=1){
				bdd_decrement_table("demande");
				--size;
			}
			--i;
			fseek(file,sizeof(Demande)*(size-1),SEEK_SET);
			fread(&dernierDemande,sizeof(Demande),1,file);
			fseek(file,i*(sizeof(Demande)),SEEK_SET);
		}
		
	}
	fclose(file);
	return 0;
}
void bdd_afficher_demande(){
	int size = bdd_getSize_table("demande");
	int i =0;
	Demande demande;
	FILE * file = NULL;
	file = fopen("rsc/demande.dat","r");
	while(fread(&demande,sizeof(Demande),1,file) != EOF && i < size){
		printf("id_utilisateur : %lu\tid_seveur:%lu\n",demande.user_id,demande.server_id);
		++i;
	}
	fclose(file);
}
	
