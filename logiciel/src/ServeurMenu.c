#include "../headers/ServeurMenu.h"


int menuServeur(unsigned long int idServ, unsigned long int idUtilisateur) {
    	char buffer[128];
    	int Admin= isAdmin(idUtilisateur, idServ);
    	do{
    		prompt_serveur(idUtilisateur , idServ);
    	
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
		
		if(strcmp(commande, "help") == 0) helpServeur(idServ, idUtilisateur);
		else if(strcmp(commande, "invite") == 0 && Admin==1 ) invitation(idServ);
		else if(strcmp(commande, "listdemande") == 0 && Admin==1 )list_demande(idServ);
		else if(strcmp(commande, "accept") == 0 && Admin==1 ) accept(idServ);
		else if(strcmp(commande, "role") == 0 && Admin==1 ) assignationRole(idServ);
		else if(strcmp(commande, "create") == 0 && Admin==1 || strcmp(commande, "mkdir")==0 && Admin==1) createSalon(idServ);
		else if(strcmp(commande, "delete") == 0 && Admin==1) deleteSalon(idServ);
		else if(!(strcmp(commande, "perm"))&& Admin==1) permServeur(idServ);
		
		else if(strcmp(commande, "listesalon") == 0 || (strcmp(commande, "ls")==0)) listeSalon(idServ, idUtilisateur);
		else if((strcmp(commande, "listemembres")==0)) listeMembres(idServ);
		else if((strcmp(commande, "open")==0) || (strcmp(commande, "cd")==0)){
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
		}
		else if(strcmp(commande, "perm") == 0 || (strcmp(commande, "chmod")==0)) permServeur(idServ);
		else if((strcmp(commande, "back") == 0 ) || (strcmp(commande, "cd..")==0)) return 1;
		else if((strcmp(commande, "exit") == 0 )) return 0;
		else printf("%s: Action inexistante\n", commande);
	}while(1);
}

void helpServeur(unsigned long int idServ, unsigned long int idUtilisateur) {
	printf("!help :\n\tPermet d'afficher toutes les commandes de ce menu\n");
	printf("\n!listesalon:\n\tAffiche la liste des salons disponible\n");
	printf("\n!listemembres :\n\tPermet d'afficher les membres/role du serveur\n");
	printf("\n!back :\n\tRetour à l'accueil\n");
	printf("\n!exit :\n\tQuitter\n");
	if(isAdmin(idUtilisateur, idServ))
	{
		printf("\nADMINISTRATION\n");
		printf("\n!role \"pseudonyme\" \"nom du role\" :\n\tPermet d'affecter un membre à un rôle\n");
		printf("\n!perm \"nom de rôle\" \"permissions\" :\n\tPermet de créer un rôle\n");
		printf("\n!invite \"pseudonyme\" :\n\tPermet d'inviter un utilisateur\n");
		printf("\n!accept \"pseudonyme\" :\n\tPermet d'accepter l'inviation d'un utilisateur\n");
		printf("\n!create \"nom de salon\" :\n\tPermet de créer un salon\n");
		printf("\n!delete \"nom du salon\" :\n\tPermet de détruire un salon\n");
	}
}

int invitation(unsigned long int idServ) {
	char *pseudo = strtok(NULL, " "); 
	unsigned long int idU = bdd_getUtilisateur_id(pseudo);
	
	if(bdd_check_membre(idServ,idU)){
		printf("%s est deja membre de ce serveur\n", pseudo);
		return 2;
	}
	
	if (idU == 0) {
		printf("\n%s n'existe pas !\n", pseudo);
		return 0;		
	}
	FILE * fichier=NULL;
	fichier = fopen("rsc/demande.dat","r");
	Demande demande;
	for(int i = 0; i < bdd_getSize_table("demande") && fread(&demande, sizeof(Demande), 1, fichier);++i) {
		if(demande.user_id == idU, demande.server_id == idServ) {
			bdd_creer_membre(idServ, idU, "Membre");
			printf("%s est devenu membre du serveur\n", pseudo);
			bdd_supprimer_invitation(idU, idServ);
			bdd_supprimer_demande(idU, idServ);
			fclose(fichier);
			return 0;		
		}
	}
	
	fclose(fichier);
	fichier = fopen("rsc/invitation.dat", "r");
	
	Invitation invitation;
	
	for(int i = 0; i < bdd_getSize_table("invitation") && fread(&invitation, sizeof(Invitation), 1, fichier) != EOF; ++i) {
		if(invitation.user_id == idU && invitation.server_id == idServ) {
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
			bdd_creer_membre(idServ, idU, "Membre");
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



void listeSalon(unsigned long int idServ, unsigned long int idUtilisateur) {

	FILE *fichier = fopen("rsc/membre.dat", "r");
	
	Membre membre;
	char nomRole[30];
	
	int i = 0;
	while(i < bdd_getSize_table("membre") && fread(&membre, sizeof(Membre), 1, fichier) != EOF) {
		if(membre.idUtilisateur == idUtilisateur && idServ == membre.idServeur) {
			strcpy(nomRole, membre.role);
			break;
		}
		++i;
	}

	fclose(fichier);
	
	fichier = fopen("rsc/salon.dat", "r");
	
	Salon salon;
	printf("Salon[%d]\n",getSalon(idServ));
	for(i = 0; i < bdd_getSize_table("salon") && fread(&salon, sizeof(Salon), 1, fichier) != EOF ; ++i) {
		if(salon.idServeur == idServ) {
			FILE *fichier2 = fopen("rsc/permission_salon.dat", "r");
			Permissions_Salon PS;
			for(int y = 0; y < bdd_getSize_table("permission_salon") && fread(&PS, sizeof(Permissions_Salon), 1, fichier2);++y) {
				if(PS.id_salon == salon.idSalon)
				{
					if(PS.perms[0] == 'r' || bdd_getProprietaireServeur_id(idServ))
					{
						printf("\t%s\n", salon.nom);
					}break;
				}
			}fclose(fichier2);
		}
	}
	fclose(fichier);
}


int assignationRole(unsigned long int idServ) {
	char *pseudo = strtok(NULL, " ");
	char *nomRole = strtok(NULL, " ");	
	int i = 0;
	int roleExist=0;
	int size=bdd_getSize_table("permission_serveur") ;
	if(pseudo==NULL || nomRole== NULL){
		return -2;
	}
	Permissions_Serveur perm;
    	FILE * file2 = NULL;
    	file2 = fopen("rsc/permission_serveur.dat","r");
    	rewind(file2); //mettre curseur au début du fichier
    
    	while(fread(&perm,sizeof(Permissions_Serveur),1,file2) != EOF && i < size && roleExist==0){   
        ++i;
        if(perm.id_serveur==idServ && strcmp(perm.Role,nomRole)==0){  //si l'id correspond
            fclose(file2);
            roleExist=1;
	    continue;
        }
   	if (i == bdd_getSize_table("permission_serveur")){
		printf("Le role %s n'existe pas\n", nomRole);
		return 1;
    	}
    	}
	FILE *fichier = fopen("rsc/membre.dat", "r+");
	Membre membre;
	i=0;
	int sizeMembre=bdd_getSize_table("membre") ;
	unsigned long int user_id=bdd_getUtilisateur_id(pseudo);
	
	
	
	
	for(i = 0; i < sizeMembre && fread(&membre, sizeof(Membre), 1, fichier) != EOF ; ++i) {
		if(membre.idUtilisateur == user_id) {
			strcpy(membre.role, nomRole);
			fseek(fichier, -sizeof(Membre), SEEK_CUR);
			fwrite(&membre, sizeof(Membre), 1, fichier);
			printf("%s est désormais %s\n", pseudo, nomRole);
			fclose(fichier);
			return 0;
		}
	}
	if (i == bdd_getSize_table("membre")){
		printf("%s n'est pas membre du serveur\n", pseudo);
	}
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

int isAdmin(unsigned long int id_user,unsigned long int id_serveur){ 
    int size = bdd_getSize_table("membre");
    if(size==0)return 0;
    int i =0;
    Membre membre;
    char monRole[40];
    FILE * file = NULL;
    file = fopen("rsc/membre.dat","r");
    rewind(file); //mettre curseur au début du fichier
    
    while(fread(&membre,sizeof(Membre),1,file) != EOF && i < size){   //read tant que la taille max du fichier est atteinte
        ++i;
        if(membre.idUtilisateur==id_user && membre.idServeur==id_serveur){  //si l'id correspond, et que le serveur aussi
             strcpy(monRole,membre.role); //recuperation du role
        }
    }
    fclose(file);
    size = bdd_getSize_table("permission_serveur");
    if(size==0)return 0;
    i =0;
    Permissions_Serveur perm;
    
    FILE * file2 = NULL;
    file2 = fopen("rsc/permission_serveur.dat","r");

    rewind(file2); //mettre curseur au début du fichier
    
    while(fread(&perm,sizeof(Permissions_Serveur),1,file2) != EOF && i < size){   //read tant que la taille max du fichier est atteinte
        ++i;
        if(perm.id_serveur==id_serveur && strcmp(perm.Role,monRole)==0 && perm.perms[1]=='x' || bdd_getProprietaireServeur_id(id_serveur)==id_user){  //si l'id correspond
            fclose(file2);
            return 1;
        }
    }
    fclose(file2);
    return 0;        
}

void listeMembres(unsigned long int idServ) {

	FILE *fichier = fopen("rsc/membre.dat", "r");
	FILE *fichier2 = fopen("rsc/utilisateur.dat", "r");
	Membre membre;
	Utilisateur utilisateur;
	char nomRole[30];
	char nomUser[30];
	int i = 0;
	printf("\nMembres : [%d]\n",getMembres(idServ));
	permMembres(idServ);
	while(i < bdd_getSize_table("membre") && fread(&membre, sizeof(Membre), 1, fichier) != EOF) 
	{	
		if(idServ == membre.idServeur) 
		{
			for(int y=0 ; y < bdd_getSize_table("utilisateur"); y++) 
			{
				fread(&utilisateur, sizeof(Utilisateur), 1, fichier2);
				if(membre.idUtilisateur == utilisateur.id)
				{	
					printf("\t%s : %s\n", utilisateur.pseudo, membre.role);
					break;
				}
			}
		}
	i++;
	}
	fclose(fichier2);
	fclose(fichier);	
}
void permMembres(unsigned long int idServ) {

	int size = bdd_getSize_table("permission_serveur");
	FILE *fichier = fopen("rsc/permission_serveur.dat", "r");
	Permissions_Serveur perm;
	char nomRole[30];
	int i = 0;
	
	while(i < size && fread(&perm, sizeof(Permissions_Serveur), 1, fichier) != EOF) 
	{	
		if(perm.id_serveur==idServ) 
		{
			printf("%s [%s]\n", perm.Role, perm.perms);
		
		}
	i++;
	}
	fclose(fichier);
	return;
}
int getMembres(unsigned long int idServ) {

	int size = bdd_getSize_table("membre");
	FILE *fichier = fopen("rsc/membre.dat", "r");
	Membre membres;
	int i = 0;
	int count=0;	
	while(i < size && fread(&membres, sizeof(Membre), 1, fichier) != EOF) 
	{	
		if(membres.idServeur==idServ) 
		{
			count++;
		
		}
	i++;
	}
	fclose(fichier);
	return count;
}
int getSalon(unsigned long int idServ) {

	int size = bdd_getSize_table("salon");
	FILE *fichier = fopen("rsc/salon.dat", "r");
	Salon salon;
	int i = 0;
	int count=0;	
	while(i < size && fread(&salon, sizeof(Salon), 1, fichier) != EOF) 
	{	
		if(salon.idServeur==idServ) 
		{
			count++;
		
		}
	i++;
	}
	fclose(fichier);
	return count;
}

int permServeur(unsigned long int idServ){
	char *role = strtok(NULL, " ");
    	char *perm = strtok(NULL, " ");
    	printf("\n\n%s : %c%c\n", role, perm[0],perm[1]);
    	if(strlen(role)>30 || strlen(perm)!=2 || perm[0]!='w' && perm[0]!='-' || perm[1]!='x' && perm[1]!='-'){ //cas derreur
    		printf("Commande invalide\n");
    		return -1;
    	}
    	//insert_perm_salon(idServ, role, perm);
	insert_perm_serveur(idServ, role, perm); //appel de la fonction pour attribuer les role de chacun au serv
	return 0;
}

/*
int permServeur(unsigned long int idServ){
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
*/


int list_demande(unsigned int long id_serveur){
	int size = bdd_getSize_table("demande");
	FILE * file = NULL;
	file = fopen("rsc/demande.dat","r");
	if(file==NULL)return -1;
	Demande demande;
	for(int i=0;i<size;++i){
		fread(&demande,sizeof(Demande),1,file);
		if(demande.server_id== id_serveur){
			int sizeUser = bdd_getSize_table("utilisateur");
			FILE *file2=NULL;
			file2 = fopen("rsc/utilisateur.dat","r");
			Utilisateur utilisateur;
			for(int j=0;j<sizeUser;++j){
				fread(&utilisateur,sizeof(Utilisateur),1,file2);
				if(demande.user_id==utilisateur.id){
					printf("%s\n",utilisateur.pseudo);
					break;
				}
			}
			fclose(file2);
		}
	}
	fclose(file);
	return 0;
}

int checkRoleServ(unsigned int long id_serveur, char Role[]){
	int i = 0;
	int size=bdd_getSize_table("permission_serveur") ;
	Permissions_Serveur perm;
    	FILE * file2 = NULL;
    	file2 = fopen("rsc/permission_serveur.dat","r");
    	rewind(file2); //mettre curseur au début du fichier
    
    	while(fread(&perm,sizeof(Permissions_Serveur),1,file2) != EOF && i < size){   
        ++i;
        if(perm.id_serveur==id_serveur && strcmp(perm.Role,Role)==0){  //si l'id correspond
            fclose(file2);
	    return 1;
        }
   	if (i == bdd_getSize_table("permission_serveur")){
		printf("Le role %s n'existe pas\n", Role);
		fclose(file2);
		return 0;
    	}
}
}
