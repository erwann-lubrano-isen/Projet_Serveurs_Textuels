#include "../headers/Acceuil_Actions.h"

int menu_Acceuil(unsigned long int user_id){
    char buffer[128];

    do{
    	prompt_acceuil(user_id);
    	
    	fgets(buffer, 127, stdin);
    	if(buffer[0]==' '){
    		printf("Action inexistante\n");
    		continue;
    	}
    	int lenght = strlen(buffer); 
    	if(lenght<=1)continue;    
    	buffer[lenght-1]=' ';
    	buffer[lenght]='\0';
    	
    	char *commande = strtok(buffer, " ");
   
    	if(!(strcmp(commande, "help")))help_acceuil();
    	else if(strcmp(commande, "create")==0 || strcmp(commande, "mkdir")==0)create_serv(user_id);
    	else if(!(strcmp(commande, "join")))join_serv(user_id);
    	else if(!(strcmp(commande, "delete")))delete_serveur(user_id);
    	else if(strcmp(commande, "listserver")==0||strcmp(commande, "ls")==0)list_serv(user_id);
    	
    	else if(strcmp(commande, "listinvitation")==0||strcmp(commande, "li")==0)list_invit(user_id);
		else if(strcmp(commande, "logout") == 0 || strcmp(commande, "cd..")==0)return 1;
    	else if(!(strcmp(commande, "exit"))) return 0;
    	else if(!(strcmp(commande, "quit")))quit_serv(user_id);
    	else if(!(strcmp(commande, "die"))){
    		bdd_supprimer_utilisateur(user_id);
    		printf("Utilisateur %lu supprimé\n", user_id);
    		return 1;
    	}
    	else if((strcmp(commande, "open")==0)|| (strcmp(commande, "cd")==0)){
    		unsigned long int id_serveur = openServeur(user_id);
    		if(id_serveur!=0){
    			if(menuServeur(id_serveur,user_id)==0)return 0;
    		}
    	}
    	else if(!(strcmp(commande, "debug"))){
    		bdd_afficher_serveurs();
    		bdd_afficher_membres();	
    	}
    	else printf("Action inexistante\n");

    }while(1);    
    return 0;
}

void help_acceuil(){
	printf("\e[1;34m----------------------------------[LISTE DES COMMANDES]-------------------------------\t|\e[0m\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mcreate/mkdir 'serverName'\e[0m\t\e[1;5m----->\e[0m\t\e[3;36mCreer un serveur\e[0m\t\t\t\e[1;34m|\e[0m\n"); 
	printf("\t\e[4;40;33mjoin 'serverName\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mDemander a rejoindre un serveur\e[0m\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mquit 'serverName'\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mQuitter un serveur\e[0m\t\t\t\e[1;34m|\e[0m\n");
	
	printf("\t\e[4;40;33mdelete 'serverName'\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mSupprimer votre serveur\e[0m\t\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mlistserver/ls\e[0m\t\t\t\e[1;5m----->\e[0m\t\e[3;36mListe des serveurs disponible\e[0m\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mlistinvitation/li\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mListe des invitations disponible\e[0m\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33maccept 'servername'\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mAccepte une invitation disponible\e[0m\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mopen/cd'servername'\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mAller dans un serveur disponible\e[0m\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mlogout\e[0m\t\t\t\t\e[1;5m----->\e[0m\t\e[3;36mSe deconnecter disponible\e[0m\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mdie\e[0m\t\t\t\t\e[1;5m----->\e[0m\t\e[3;36mSupprimer le compte disponible\e[0m\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mexit\e[0m\t\t\t\t\e[1;5m----->\e[0m\t\e[3;36mQuitter le programme\e[0m\t\t\t\e[1;34m|\e[0m\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\e[1;34m|\e[0m\e[0m");
	printf("\n\e[1;34m______________________________________________________________________________________\t|\e[0m\n");
}

int create_serv(unsigned long int idProprio){
	char * servname=strtok(NULL," ");

	if(servname==NULL || strlen(servname)>30 || strlen(servname) > 30){
		printf("\e[1;31mCommande incorrecte\e[0m\n");
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
			printf("\e[1;31mCe nom de serveur existe deja\e[0m\n");
			return 1;
		}
		++i;
	}
	fclose(fichier);
	if (bd_creationServeur(servname,idProprio)==0 && bdd_creer_membre(bdd_getServeur_id(servname), idProprio, "Admin")==0){
		printf("\e[1;32m- Le serveur '%s' a bien été crée\n", servname);
	}
	
	
	return 0;
}

int delete_serveur(unsigned long int user_id){	
	char * serveur_name=strtok(NULL," ");
	if(serveur_name == NULL || strlen(serveur_name)>30){
		printf("\e[1;31mCommande incorrecte\e[0m\n");
		return -1;
	}
	
	unsigned long serveur_id=bdd_getServeur_id(serveur_name);
	
	if(serveur_id==0){
		printf("\e[1;31mServeur inconnu\e[0m\n");
		return 1;
	}
	FILE * fichier;
	Serveur serveur;
	fichier = fopen("rsc/serveur.dat","r+");
	int size = bdd_getSize_table("serveur");
	int i=0;
	if(fichier == NULL)return -1;
	while(fread(&serveur,sizeof(Serveur),1,fichier)!=EOF&&i<size){
		if(serveur.id==serveur_id){
			fclose(fichier);
			if(serveur.idProprio == user_id){
				bd_suppressionServeur(serveur.id);
				return 0;
			}else{
				printf("\e[1;31mCe serveur ne vous appartient pas\e[0m\n");
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
		printf("\e[1;31mCommande incorrecte\e[0m\n");
		return 1;
	}
	unsigned long int idServ = bdd_getServeur_id(servername);
	if(bdd_check_membre(idServ,userid)){
		printf("\e[1;31mVous etes deja membre de ce serveur\e[0m\n");
		return 2;
	}
	
	FILE * fichier = fopen("rsc/invitation.dat","r");
	Invitation invitation;
	
	
	for(int i = 0; i < bdd_getSize_table("invitation") && fread(&invitation, sizeof(Invitation), 1, fichier) != EOF; ++i) {
		if(invitation.user_id == userid && invitation.server_id == idServ) {
			bdd_creer_membre(idServ, userid, "Membre");
			printf("Vous avez rejoint %s\n", servername);
			bdd_supprimer_invitation(userid, idServ);
			bdd_supprimer_demande(userid, idServ);
			fclose(fichier);
			return 0;
		}
	}
	fclose(fichier);
	Demande demande;
	unsigned long int serveur_id=bdd_getServeur_id(servername);
	if(serveur_id==0){
		printf("\e[1;31mServeur inexistant\e[0m\n");
		return 1;
	}
	fichier = fopen("rsc/demande.dat","r");
	int size = bdd_getSize_table("demande");
	int i=0;
	
	
	if(fichier == NULL)return -1;
	while(fread(&demande,sizeof(Demande),1,fichier)!=EOF&&i<size){
		if(serveur_id==demande.server_id && demande.user_id==userid){
			fclose(fichier);
			printf("\e[1;31mDemande deja existante!\e[0m\n");
			return 1;
		}
		++i;
	}
	fclose(fichier);
	bdd_stock_demande(userid,serveur_id);
	printf("Demande envoyé à %s\n", servername);
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
			int sizes = bdd_getSize_table("serveur");
			if(file == NULL)return -1;
			int j=0;
			while(fread(&serveur,sizeof(Serveur),1,file)!=EOF&&j<sizes){
				if(membre.idServeur==serveur.id){
					printf("\t%s\n",serveur.nom);
				}
				++j;
			}
		}
		++i;
	}
	fclose(fichier);
	return 0;
}

	
int list_invit(unsigned int long user_id){
	FILE * fichier;
	fichier = fopen("rsc/invitation.dat","r");
	Invitation invitation;
	int size = bdd_getSize_table("invitation");
	if(fichier == NULL)return -1;
	int i=0;
	while(fread(&invitation,sizeof(Invitation),1,fichier)!=EOF&&i<size){
		if(invitation.user_id==user_id){
			FILE * file;
			file = fopen("rsc/serveur.dat","r");
			Serveur serveur;
			int sizes = bdd_getSize_table("serveur");
			if(file == NULL)return -1;
			int j=0;
			while(fread(&serveur,sizeof(Serveur),1,file)!=EOF&&j<sizes){
				if(invitation.server_id==serveur.id){
					printf("\t%s\n",serveur.nom);
				}
				++j;
			}
			break;
		}
		++i;
	}
	fclose(fichier);
	return 0;
}


int quit_serv(unsigned long int userid){
	char * servername=strtok(NULL," ");
	if(servername==NULL || strlen(servername)>30){
		printf("\e[1;31mCommande incorrecte\e[0m\n");
		return 1;
	}
	FILE * fichier = fopen("rsc/serveur.dat", "r+");
	//FILE * file = fopen("rsc/membre.dat", "r+");
	//Membre membre;
	Serveur serveur;

	unsigned long int serveur_id=bdd_getServeur_id(servername);
	if(serveur_id==0){
		printf("\e[1;31mServeur inexistant\e[0m\n");
		return 1;
	}
	for(int i = 0; i < bdd_getSize_table("serveur") && fread(&serveur, sizeof(Serveur), 1, fichier) != EOF; ++i) {
		if (serveur_id == serveur.id && userid == serveur.idProprio) {
			printf("\e[1;31mImpossible pour le propietaire du serveur\e[0m\n");
			fclose(fichier);
			return 0;
		}
	}
	fclose(fichier);
	/*
	for(int j = 0; j < bdd_getSize_table("membre") && fread(&membre, sizeof(Membre), 1, file) != EOF; ++j) {
		if (serveur_id == membre.idServeur && userid == membre.idUtilisateur) {
			fseek(file, sizeof(Membre)*(bdd_getSize_table("membre")-1), SEEK_SET); //Positionnement du curseur au début de la dernière ligne
			fread(&membre, sizeof(Membre), 1, file);	//Obtention de la dernière ligne dans serveur
			fseek(file, sizeof(Membre)*(j-1), SEEK_SET); //Positionnement au début de la ligne i
			fwrite(&membre, sizeof(Membre), 1, file);	//Ecriture de la dernière ligne contenue dans serveur
			bdd_decrement_table("membre");
			return 0;
		}
	}
	fclose(file);
*/
	bdd_supprimer_membre(serveur_id, userid);
	return 0;
}

unsigned long int openServeur(unsigned int long user_id){
	char * servername=strtok(NULL," ");
	if(servername==NULL || strlen(servername)>30){
		printf("\e[1;31mCommande incorrecte\e[0m\n");
		return 0;
	}
	unsigned long int serveur_id=bdd_getServeur_id(servername);
	if(serveur_id==0){
		printf("serveur inexistant\n");
	}else if(bdd_check_membre(serveur_id,user_id)){
		return serveur_id;
	}else{
		printf("\e[1;31mVous n'etes pas membre de ce serveur\e[0m\n");
	}
	return 0;
}

void prompt_acceuil(unsigned long int user_id){
	int size = bdd_getSize_table("utilisateur");
	int i =0;
	Utilisateur utilisateur;
	FILE * file = NULL;
	file = fopen("rsc/utilisateur.dat","r");
	while(fread(&utilisateur, sizeof(Utilisateur), 1, file) != EOF && i <= size){
		if(user_id==utilisateur.id){
			fclose(file);
			printf(">\e[33m%s\e[0m $ ",utilisateur.pseudo);
			return;
		}
		++i;
	}
	fclose(file);
}
void auRevoir(unsigned long int user_id){
	int size = bdd_getSize_table("utilisateur");
	int i =0;
	Utilisateur utilisateur;
	FILE * file = NULL;
	file = fopen("rsc/utilisateur.dat","r");
	while(fread(&utilisateur, sizeof(Utilisateur), 1, file) != EOF && i <= size){
		if(user_id==utilisateur.id){
			fclose(file);
			printf("\n\e[1;33;44mAu revoir %s !\e[0m\n", utilisateur.pseudo);
			return;
		}
		++i;
	}
	fclose(file);
}
