#include "../headers/Acceuil_Actions.h"

void help_acceuil(){
printf("Commandes disponibles au menu acceuil :\n");
printf("\t!create servername\n");
printf("\t!join serverID\n");
printf("\t!quit serverID\n");
printf("\t!delete serverID\n");
printf("\t!listserver\n");
printf("\t!listinvitation\n");
printf("\t!accept serverID (invitation)\n");
printf("\t!open serverID\n");
printf("\t!exit\n");
printf("\t!logout\n");
printf("\t!die\n");
}

int create_serv(char commande[], unsigned long int idProprio){
	char * cmd=strtok(commande," ");
	char * servname=strtok(NULL," ");

	if(servname==NULL || strlen(servname)>30 || strlen(servname) > 30){
		printf("commande incorrecte\n");
		return 1;
	}
	FILE * fichier;
	Serveur serveur;
	fichier = fopen("rsc/serveur.dat","r");
	int size = bdd_getSize_table("serveur");
	int i=0;
	if(fichier == NULL)return -1;
	while(fread(&serveur,sizeof(Serveur),1,fichier)!=EOF&&i<size){
		if(strcmp(servname,serveur.nom)==0){
			fclose(fichier);
			printf("Ce nom de serveur existe deja!\n");
			return 1;
		}
		++i;
	}
	fclose(fichier);
	bd_creationServeur(servname,idProprio);
	return 0;
}
