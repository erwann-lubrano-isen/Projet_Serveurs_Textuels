#include "../headers/Connexions_Action.h"



void affich_help(){
puts("gfre");
	printf("Liste des commandes disponibles : \n");
	printf("\t !login userID MotDePasse \n");
	printf("\t !signup pseudo MotDePasse \n");
	printf("\t !create servername \n");
	printf("\t !join serverID \n");
	printf("\t !quit serverID \n");
	printf("\t !delete serverID \n");
	printf("\t !listserver \n");
	printf("\t !listinvitation \n");
	printf("\t !accept serverID (invitation) \n");
	printf("\t !open serverID \n");
	printf("\t !exit \n");
	printf("\t !logout\n");
	printf("\t !die \n");
}

int signup(char commande[]){
	char * cmd=strtok(commande," ");
	char * pseudo=strtok(NULL," ");
	char * motdepasse=strtok(NULL," ");
	if(strlen(pseudo)>30 || strlen(motdepasse) > 30){
		printf("commande incorrecte\n");
		return 1;
	}
	FILE * fichier;
	Utilisateur utilisateur;
	fichier = fopen("rsc/utilisateur.dat","r");
	int size = bdd_getSize_table("utilisateur");
	int i=0;
	if(fichier == NULL)return -1;
	while(fread(&utilisateur,sizeof(Utilisateur),1,fichier)!=EOF&&i<size){
		if(strcmp(pseudo,utilisateur.pseudo)==0){
			fclose(fichier);
			printf("Ce pseudo est deja pris !\n");
			return 1;
		}
		++i;
	}
	fclose(fichier);
	bdd_creer_utilisateur(pseudo, motdepasse);
	return 0;
}

unsigned long int  login(char commande[]){
	char * cmd=strtok(commande," ");
	char * pseudo=strtok(NULL," ");
	char * motdepasse=strtok(NULL," ");
	if(strlen(pseudo)>30 || strlen(motdepasse) > 30){
		printf("commande incorrecte\n");
		return 0;
	}
	FILE * fichier;
	Utilisateur utilisateur;
	fichier = fopen("rsc/utilisateur.dat","r");
	int size = bdd_getSize_table("utilisateur");
	int i=0;
	if(fichier == NULL)return 0;
	while(fread(&utilisateur,sizeof(Utilisateur),1,fichier)!=EOF&&i<size){
		if(strcmp(pseudo,utilisateur.pseudo)==0){
			
			if(strcmp(motdepasse,utilisateur.motDePasse)==0){
				fclose(fichier);
				printf("Connecte !\n");
				return utilisateur.id;
			}
			printf("Mot de passe incorrecte\n");
			fclose(fichier);
			return 0;
		}
		++i;
	}
	printf("utilisateur inexistant\n");
	fclose(fichier);
	return 0;
}


