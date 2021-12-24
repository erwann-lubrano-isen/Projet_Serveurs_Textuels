#include "../headers/Connexions_Action.h"




void affich_help(){
	printf("\e[1;34m--------------------------[LISTE DES COMMANDES]-----------------------\t|\e[0m\n");
	printf("\t\t\t\t\t\t\t\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mlogin 'pseudo' 'passWord'\e[0m\t\e[1;5m----->\e[0m\t\e[3;36mSe connecter\e[0m\t\t\e[1;34m|\e[0m\n"); 
	printf("\t\e[4;40;33msignup 'pseudo' 'passWord'\e[0m\t\e[1;5m----->\e[0m\t\e[3;36mSe connecter\e[0m\t\t\e[1;34m|\e[0m\n"); 
	printf("\t\e[4;40;33mexit\e[0m\t\t\t\t\e[1;5m----->\e[0m\t\e[3;36mQuitter le programme\e[0m\t\e[1;34m|\e[0m\n");
	printf("\t\t\t\t\t\t\t\t\t\e[1;34m|\e[0m\e[0m");	printf("\n\e[1;34m______________________________________________________________________\t|\e[0m\n");

}

int signup(){
	char * pseudo=strtok(NULL," ");
	char * motdepasse=strtok(NULL," ");
	if(pseudo == NULL || motdepasse == NULL || strlen(pseudo)>30 || strlen(motdepasse) > 30){
		printf("\e[1;31mcommande incorrecte\e[0m\n");
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
			printf("\e[1;31mCe pseudo est deja pris !\e[0m\n");
			return 1;
		}
		++i;
	}
	fclose(fichier);
	bdd_creer_utilisateur(pseudo, motdepasse);
	printf("\e[1;32m- utilisateur %s créé\e[0m\n",pseudo);
	return 0;
}

unsigned long int  login(){
	char * pseudo=strtok(NULL," ");
	char * motdepasse=strtok(NULL," ");
	if(pseudo == NULL || motdepasse == NULL || strlen(pseudo)>30 || strlen(motdepasse) > 30){
		printf("\e[1;31mcommande incorrecte\e[0m\n");
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
				printf("\e[1;32mConnecté !\e[0m\n");
				return utilisateur.id;
			}
			printf("\e[1;31mMot de passe incorrecte\e[0m\n");
			fclose(fichier);
			return 0;
		}
		++i;
	}
	printf("\e[1;31mutilisateur inexistant\e[0m\n");
	fclose(fichier);
	return 0;
}

int menuConnexion() {
    char buffer[128];
    
    do{
    	connexion_prompt();
    	
    	fgets(buffer, 127, stdin);
    	if(buffer[0]==' '){
    		printf("\e[1;31mAction inexistante\e[0m\n");
    		continue;
    	}
    	int lenght = strlen(buffer); 
    	if(lenght<=1)continue;    
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
    	else printf("\e[1;31mAction inexistante\n\e[0m");
    }while(1);    
    return 0;
}

void connexion_prompt(){
	printf("\e[0m>$ ");
}


