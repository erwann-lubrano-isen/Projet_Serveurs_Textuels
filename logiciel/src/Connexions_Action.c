#include "../headers/Connexions_Action.h"




void affich_help(){
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

int signup(){
	char * pseudo=strtok(NULL," ");
	char * motdepasse=strtok(NULL," ");
	if(pseudo == NULL || motdepasse == NULL || strlen(pseudo)>30 || strlen(motdepasse) > 30){
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

unsigned long int  login(){
	char * pseudo=strtok(NULL," ");
	char * motdepasse=strtok(NULL," ");
	if(pseudo == NULL || motdepasse == NULL || strlen(pseudo)>30 || strlen(motdepasse) > 30){
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

int menuConnexion() {
    char buffer[128];
    
    do{
    	connexion_prompt();
    	fgets(buffer, 127, stdin);
    	int lenght = strlen(buffer);
    	if(lenght==1)continue;
    	buffer[lenght-1]=' ';
    	buffer[lenght]='\0';
    	char *commande = strtok(buffer, " ");
    	
    	if(!(strcmp(commande, "help"))) affich_help();
    	else if(!(strcmp(commande, "signup"))) signup();
    	else if(!(strcmp(commande, "login"))){
    		unsigned long int user_id=login();
    		if(user_id!=0) {
    			if(menu_Acceuil(user_id)==0)return 0;
    		}
    	}else if(!(strcmp(commande, "exit"))) return 0;
    	else printf("Action inexistante\n");
    }while(1);    
    return 0;
}

void connexion_prompt(){
	printf(">$ ");
}


