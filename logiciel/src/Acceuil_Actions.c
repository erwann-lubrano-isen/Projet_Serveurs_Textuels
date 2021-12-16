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
    	else if(!(strcmp(commande, "!create")))create_serv(user_id);
    	else if(!(strcmp(commande, "!listeserv")))list_serv(user_id);
    	else if(!(strcmp(commande, "!debug"))){
    		bdd_afficher_serveurs();
    		bdd_afficher_membres();
    		
    	}else printf("Action inexistante\n");

    }while(1);    
    return 0;
}

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

int create_serv(unsigned long int idProprio){
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
	bdd_creer_membre(bdd_getServeur_id(servname), idProprio, "Admin");
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
		return 1;
	}
	FILE * fichier;
	Serveur serveur;
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
	fclose(fichier);
	return 0;
}

int join_serv(unsigned long int userid){
	char * servername=strtok(NULL," ");
	if(servername==NULL || strlen(servername)>30){
		printf("commande incorrecte\n");
		return 1;
	}
	FILE * fichier;
	Demande demande;
	unsigned long int serveur_id=bdd_getServeur_id(servername);
	if(serveur_id==0){
		printf("Serveur inexistant\n");
		return 1;
	}
	fichier = fopen("rsc/demande.dat","r");
	int size = bdd_getSize_table("demande");
	int i=0;
	
	
	if(fichier == NULL)return -1;
	while(fread(&demande,sizeof(Demande),1,fichier)!=EOF&&i<size){
		if(serveur_id==demande.server_id){
			fclose(fichier);
			printf("demande deja existante!\n");
			return 1;
		}
		++i;
	}
	fclose(fichier);
	bdd_stock_demande(userid,serveur_id);
	return 0;
}

int list_serv(unsigned int long user_id){
	FILE * fichier;
	fichier = fopen("rsc/membre.dat","r");
	Membre membre;
	int size = bdd_getSize_table("membre");
	if(fichier == NULL)return -1;
	int i=0;
	while(fread(&membre,sizeof(Membre),1,fichier)!=EOF&&i<size){
		if(membre.idUtilisateur==user_id){
			FILE * file;
			file = fopen("rsc/serveur.dat","r");
			Serveur serveur;
			int size = bdd_getSize_table("serveur");
			if(file == NULL)return -1;
			int j=0;
			while(fread(&serveur,sizeof(Serveur),1,file)!=EOF&&j<size){
				if(membre.idServeur=serveur.id){
					printf("\t%s\n",serveur.nom);
				}
				++j;
			}
		}
		++i;
	}
	fclose(fichier);
}
