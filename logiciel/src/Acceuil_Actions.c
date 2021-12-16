#include "../headers/Acceuil_Actions.h"

int menu_Acceuil(unsigned long int user_id){
	char buffer[128];
    
    do{
    	fgets(buffer, 127, stdin);
    	int lenght = strlen(buffer);
    	buffer[lenght-1]=' ';
    	buffer[lenght]='\0';
    	char *commande = strtok(buffer, " ");
    	
    	if(!(strcmp(commande, "!help")));
		else if(!(strcmp(commande, "!back")))return 1;
    	else if(!(strcmp(commande, "!exit"))) return 0;
    	else printf("Action inexistante\n");
    }while(1);    
    return 0;
}

int delete_serveur(char commande[], unsigned long int user_id){
	char * serveur_name=strtok(NULL," ");
	if(serveur_name == NULL || strlen(serveur_name)>30){
		printf("commande incorrecte\n");
		return 0;
	}
	
	unsigned long serveur_id=bdd_getServeur_id(serveur_name);
	
	if(serveur_id==0){
		printf("Serveur inconnu\n");
		return 1
	}
	FILE * fichier;
	Utilisateur utilisateur;
	fichier = fopen("rsc/s.dat","r");
	int size = bdd_getSize_table("utilisateur");
	int i=0;
	if(fichier == NULL)return -1;
	while(fread(&serveur,sizeof(Serveur),1,fichier)!=EOF&&i<size){
			if(serveur.id==serveur_id){
				fclose(fichier);
				if(serveur.idProprio == user_id){
					bd_suppressionServeur(serveur.id);
					return 0;
				}else{
					printf("Ce serveur ne vous appartient pas\n");
					return 2;
				}
			}
		}
	}
	fclose(fichier);
	return 0;
}
