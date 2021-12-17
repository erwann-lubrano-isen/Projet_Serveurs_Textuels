#include "../headers/ServeurMenu.h"


int menuServeur(unsigned long int idServ, unsigned long int idUtilisateur) {
	while (1) {
		prompt_serveur(idUtilisateur,idServ);
		char buffer[128];
		fgets(buffer, 127, stdin);
		int lenght = strlen(buffer);
		if(lenght==1)continue;
		buffer[lenght-1]=' ';
		buffer[lenght]='\0';
			
			
		char *commande = strtok(buffer, " ");
		printf("\n%s\n", buffer);
		if(strcmp(commande, "help") == 0) helpServeur();
		else if(strcmp(commande, "invite") == 0) invitation(idServ);
		else if(strcmp(commande, "accept") == 0) accept(idServ);
		else if(strcmp(commande, "create") == 0) createSalon(idServ);
		else if(strcmp(commande, "delete") == 0) deleteSalon(idServ);
		else if((strcmp(commande, "role") == 0 ));
		else if((strcmp(commande, "open")==0)){
			char * salonname = strtok(NULL," ");
			if(salonname == NULL || strlen(salonname) > 30){
				printf("commande invalide\n");
			}else{
				unsigned long int salon_id = bdd_getSalon_id(idServ, salonname);
				if(salon_id==0){
					printf("Salon inexistant\n");
				}else{
					if(menuSalon(salon_id, idUtilisateur, idServ)==0)return 0;
				}
			}
		}else if(strcmp(commande, "perm") == 0 ) return 7;
		else if((strcmp(commande, "back") == 0 )) return 1;
		else if((strcmp(commande, "exit") == 0 )) return 0;
		else printf("%s: Action inexistante\n", commande);
	}
}

void helpServeur() {
	printf("!help :\n\tPermet d'afficher toutes les commandes de ce menu\n");
	printf("\n!invite \"pseudonyme\" :\n\tPermet d'inviter un utilisateur\n");
	printf("\n!accept \"pseudonyme\" :\n\tPermet d'accepter l'inviation d'un utilisateur\n");
	printf("\n!create \"nom de salon\" :\n\tPermet de créer un salon\n");
	printf("\n!delete \"nom du salon\" :\n\tPermet de détruire un salon\n");
	printf("\n!role \"pseudonyme\" \"nom du role\" :\n\tPermet d'affecter un membre à un rôle\n");
	printf("\n!perm \"nom de rôle\" \"permissions\" :\n\tPermet de créer un rôle\n");
	printf("\n!back :\n\tRetour à l'accueil\n");
	printf("\n!exit :\n\tQuitter\n");
}

int invitation(unsigned long int idServ) {
	char *pseudo = strtok(NULL, " "); 
	unsigned long int idU = bdd_getUtilisateur_id(pseudo);
	if (idU == 0) {
		printf("\n%s n'existe pas !\n", pseudo);
		return 0;		
	}
	
	FILE *fichier = fopen("rsc/invitation.dat", "r");
	
	Invitation invitation;
	
	for(int i = 0; i < bdd_getSize_table("invitation") && fread(&invitation, sizeof(Invitation), 1, fichier) != EOF; ++i) {
		if(invitation.user_id == idU && invitation.server_id) {
			printf("%s à déjà été invité dans ce serveur\n", pseudo);
			fclose(fichier);
			return 0;
		}
	}
	bdd_creer_invitation(idU ,idServ);
	fclose(fichier);
	return 0;
}

int accept(unsigned long int idServ) {
	char *pseudo = strtok(NULL, " "); 
	unsigned long int idU = bdd_getUtilisateur_id(pseudo);
	
	if (idU == 0) {
		printf("\n%s n'existe pas !\n", pseudo);
		return 0;		
	}
	
	FILE *fichier = fopen("rsc/demande.dat", "r");
	Demande demande;
	
	for(int i = 0; i < bdd_getSize_table("demande") && fread(&demande, sizeof(Demande), 1, fichier) != EOF; ++i) {
		if(demande.user_id == idU && demande.server_id == idServ) {
			bdd_supprimer_demande(idU, idServ);
			bdd_creer_membre(idServ, idU, "membre");
			printf("\n%s est devenu membre du serveur\n", pseudo);
			fclose(fichier);
			return 0;
		}
	}
	printf("Aucune demande de %s\n", pseudo);
	fclose(fichier);
	return 0;
}

int createSalon(unsigned long int idServ) {
	char *nomSalon = strtok(NULL, " ");
	if(bdd_getSalon_id(idServ ,nomSalon) == 0) {
		bdd_create_Salon(nomSalon, idServ);
	}
	else printf("Ce salon existe déjà !\n");
	return 0;
}

int deleteSalon(unsigned long int idServ) {
	char *nomSalon = strtok(NULL, " ");
	
	unsigned long int idSalon= bdd_getSalon_id(idServ, nomSalon);
	
	if(idSalon != 0) {
		bdd_supprimer_salon(idSalon, idServ);
	}
	else printf("Ce salon n'existe pas !\n");
	return 0;
}

int permServeur(unsigned long int idServ,unsigned long int idUtilisateur ){
	char *nomRole = strtok(NULL, " ");
	char *perm = strtok(NULL, " ");
	
	FILE *fichier = fopen("rsc/permission_serveur.dat", "r+");
	Permissions_Serveur PS;
	
	for(int i = 0; i < bdd_getSize_table("permission_serveur") && fread(&PS, sizeof(Permissions_Serveur), 1, fichier) != EOF ; ++i) {
		if (strcmp(PS.Role, nomRole) == 0 && PS.id_serveur == idServ) {
			strcpy(PS.perms, perm);
			printf("Les droits du rôle \"%s\" ont été modifié\n", nomRole);
			return 0;
		}
	}
	insert_perm_serveur(idServ, nomRole, perm);
	printf("Le rôle a été créé\n");
	return 0;
}

void listeSalon(unsigned long int idServ, unsigned long int idUtilisateur) {

	FILE *fichier = fopen("rsc/membre.dat", "r");
	
	Membre membre;
	char nomRole[30];
	
	int i = 0;
	while(i < bdd_getSize_table("membre_serveur") && fread(&membre, sizeof(Membre), 1, fichier) != EOF) {
		if(membre.idUtilisateur == idUtilisateur && idServ == membre.idServeur) {
			strcpy(nomRole, membre.role);
			break;
		}
		++i;
	}

	fclose(fichier);
	
	fichier = fopen("rsc/salon.dat", "r");
	
	Salon salon;
	
	for(i = 0; i < bdd_getSize_table("salon") && fread(&salon, sizeof(Salon), 1, fichier) != EOF ; ++i) {
		if(salon.idServeur == idServ) {
			FILE *fichier2 = fopen("rsc/permissions_salon.dat", "r");
			Permissions_Salon PS;
			for(int y = 0; y < bdd_getSize_table("permission_salon") && fread(&PS, sizeof(Permissions_Salon), 1, fichier);++y) {
				if(PS.id_salon == salon.idSalon)
					if(PS.perms[0] == 'r')
						printf("%s\n", salon.nom);
			}
		}
	}
	fclose(fichier);
}

int assignationRole(unsigned long int idServ) {
	char *pseudo = strtok(NULL, " ");
	char *nomRole = strtok(NULL, " ");
	
	FILE *fichier = fopen("permission_serveur.dat", "r+");
	Membre membre;
	Permissions_Serveur PS;
	int i;
	for(i = 0; i < bdd_getSize_table("permission_serveur") && fread(&PS, sizeof(Permissions_Serveur), 1, fichier) != EOF ; ++i) {//Vérification de l'existance du role
		if(strcmp(PS.Role, nomRole) == 0) {
			strcpy(membre.role, nomRole);
			break;
		}
	}
	
	if(i == bdd_getSize_table("permission_serveur")) {
		printf("Le role \"%s\" n'existe pas\n", nomRole);
		return 0;
	}
	
	if(bdd_getUtilisateur_id(pseudo) == 0) {
		printf("\n");
	
	}
	
	
	
	for(i = 0; i < bdd_getSize_table("membre") && fread(&membre, sizeof(Membre), 1, fichier) != EOF ; ++i) {
		if(membre.idUtilisateur == bdd_getUtilisateur_id(pseudo)) {
			strcpy(membre.role, nomRole);
			fseek(fichier, sizeof(Membre)*(i-1), SEEK_SET);
			fwrite(&membre, sizeof(Membre), 1, fichier);
			printf("%s est désormais %s\n", pseudo, nomRole);
			return 0;
		}
	}
	if (i == bdd_getSize_table("membre"))
		printf("%s n'est pas membre du serveur\n", pseudo);
	return 0;
}

void prompt_serveur(unsigned long int user_id, unsigned long int serveur_id){
	int size = bdd_getSize_table("utilisateur");
	int i =0;
	Utilisateur utilisateur;
	FILE * file = NULL;
	file = fopen("rsc/utilisateur.dat","r");
	while(fread(&utilisateur, sizeof(Utilisateur), 1, file) != EOF && i <= size){
		if(user_id==utilisateur.id){
				int size2 = bdd_getSize_table("serveur");
				int j =0;
				Serveur serveur;
				FILE * file2 = NULL;
				file2 = fopen("rsc/serveur.dat","r");
				while(fread(&serveur, sizeof(Serveur), 1, file2) != EOF && j <= size2){
					if(serveur_id==serveur.id){
						printf(">%s/%s $ ",utilisateur.pseudo,serveur.nom);
						fclose(file);
						fclose(file2);
						return;
					}
					++j;
				}
			fclose(file2);
		}
		++i;
	}
	fclose(file);
}

int isAdmin(unsigned long int id_user,unsigned long int id_serveur){ //EN ATTENTE DE LA FONCTION ROLE
    int size = bdd_getSize_table("membres");
    if(size==0)return 0;
    int i =0;
    Membre membre;
    char monRole[40];
    FILE * file = NULL;
    file = fopen("rsc/membres.dat","r");
    rewind(file); //mettre curseur au début du fichier
    
    while(fread(&membre,sizeof(Membre),1,file) != EOF && i < size){   //read tant que la taille max du fichier est atteinte
        ++i;
        if(membre.idUtilisateur==id_user && membre.idServeur==id_serveur){  //si l'id correspond, et que le serveur aussi
             strcpy(monRole,membre.role); //recuperation du role
             fclose(file);
        }
    }
    
    size = bdd_getSize_table("permissions_serveur");
    if(size==0)return 0;
    i =0;
    Permissions_Serveur perm;
    
    file = NULL;
    file = fopen("rsc/permission_serveur.dat","r");

    rewind(file); //mettre curseur au début du fichier
    
    while(fread(&perm,sizeof(Permissions_Serveur),1,file) != EOF && i < size){   //read tant que la taille max du fichier est atteinte
        ++i;
        if(perm.id_serveur==id_serveur && strcmp(perm.Role,monRole)==0 && perm.perms[1]=='x' || bdd_getProprietaireServeur_id(id_serveur)==id_user){  //si l'id correspond
            fclose(file); 
            return 1;
        }
    }
    
    return 0;        
}



