#include "../headers/ServeurMenu.h"


int menuServeur(unsigned long int idServ, unsigned long int idUtilisateur) {
    	char buffer[128];
    	int permX_serv = isAdmin(idUtilisateur, idServ);
    	int permW_serv = bdd_hasWPerm_serveur(idServ, idUtilisateur);
    	do{
    		prompt_serveur(idUtilisateur , idServ);
    	
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
		
		if(strcmp(commande, "help") == 0) helpServeur(idServ, idUtilisateur);
		else if(strcmp(commande, "invite") == 0 && permX_serv==1) invitation(idServ);
		else if((strcmp(commande, "listedemandes") == 0 || strcmp(commande, "ld") == 0) && permX_serv==1)list_demande(idServ);
		else if(strcmp(commande, "accept") == 0 && permX_serv==1) accept(idServ);
		else if(strcmp(commande, "role") == 0 && permX_serv==1){
			assignationRole(idServ);
			permX_serv = isAdmin(idUtilisateur, idServ);
    		permW_serv = bdd_hasWPerm_serveur(idServ, idUtilisateur);
		}else if((strcmp(commande, "create") == 0 && permW_serv==1) || (strcmp(commande, "mkdir")==0 && permW_serv==1)) createSalon(idServ);
		else if(strcmp(commande, "delete") == 0 && permW_serv==1) deleteSalon(idServ);
		else if((strcmp(commande, "perm")==0 || (strcmp(commande, "chmod")==0))&& permX_serv==1){
			permServeur(idServ);
			permX_serv = isAdmin(idUtilisateur, idServ);
    		permW_serv = bdd_hasWPerm_serveur(idServ, idUtilisateur);
		}else if(strcmp(commande, "listesalon") == 0 || (strcmp(commande, "ls")==0)) listeSalon(idServ, idUtilisateur);
		else if(strcmp(commande, "listemembres")==0 || (strcmp(commande, "lm")==0)) listeMembres(idServ);
		else if((strcmp(commande, "open")==0) || (strcmp(commande, "cd")==0)){
			char * salonname = strtok(NULL," ");
			if(salonname == NULL || strlen(salonname) > 30){
				printf("\e[1;31mCommande invalide\e[0m\n");
			}else{
				unsigned long int salon_id = bdd_getSalon_id(idServ, salonname);
				if(salon_id==0){
					printf("\e[1;31mSalon inexistant\e[0m\n");
				}
				else if (menuSalon(salon_id, idUtilisateur, idServ)==0)return 0;
				}

		}
		else if((strcmp(commande, "back") == 0 ) || (strcmp(commande, "cd..")==0)) return 1;
		else if((strcmp(commande, "exit") == 0 )){
		auRevoir(idUtilisateur);
		return 0;
		}
		else printf("%s: \e[1;31mAction inexistante\e[0m\n", commande);
	}while(1);
}

void helpServeur(unsigned long int idServ, unsigned long int idUtilisateur) {

	printf("\e[1;34m------------------------[LISTE DES COMMANDES]--------------------------\t|\e[0m\n");
	printf("\t\t\t\t\t\t\t\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mlistesalon/ls\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mAffiche la liste des salons\e[0m\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mlistemembres/lm\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mAffiche les membres du serveur\e[0m\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mopen/cd 'server'\e[0m\t\e[1;5m----->\e[0m\t\e[3;36mAller dans un salon[r]\e[0m\t\t\e[1;34m|\e[0m\n");
	
	
	if(bdd_hasWPerm_serveur(idServ, idUtilisateur)){
	printf("\t\e[4;40;33mcreate 'salon'\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mCreer un salon[w]\e[0m\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mdelete 'salon'\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mSupprimer un salon[w]\e[0m\t\t\e[1;34m|\e[0m\n");
	}
	
	
	printf("\t\e[4;40;33mback\e[0m\t\t\t\e[1;5m----->\e[0m\t\e[3;36mRetour à l'acceuil\e[0m\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mexit\e[0m\t\t\t\e[1;5m----->\e[0m\t\e[3;36mQuitter\e[0m\t\t\t\t\e[1;34m|\e[0m\n");
	printf("\t\t\t\t\t\t\t\t\t\e[1;34m|\e[0m\e[0m\n");
	
	if (isAdmin(idUtilisateur, idServ)){
		printf("\e[1;35m------------------------[ADMINISTRATION][x]----------------------------\t|\e[0m\n");
		printf("\t\t\t\t\t\t\t\t\t\e[1;35m|\e[0m\n");		
		printf("\t\e[4;40;33mrole 'pseudo' 'role'\e[0m\t\e[1;5m---->\e[0m\t\e[3;36mAffecte le role a un membre\e[0m\t\e[1;35m|\e[0m\n");
		printf("\t\e[4;40;33mperm 'role' 'perm'\e[0m\t\e[1;5m---->\e[0m\t\e[3;36mCrée/Modifier un role\e[0m\t\t\e[1;35m|\e[0m\n");
		printf("\t\e[4;40;33minvite 'pseudo'\e[0m\t\t\e[1;5m---->\e[0m\t\e[3;36mInviter au serveur\e[0m\t\t\e[1;35m|\e[0m\n");
		printf("\t\e[4;40;33maccept 'pseudo'\e[0m\t\t\e[1;5m---->\e[0m\t\e[3;36mAccepte au serveur\e[0m\t\t\e[1;35m|\e[0m\n");
		printf("\t\e[4;40;33mlistedemandes/ld\e[0m\t\e[1;5m---->\e[0m\t\e[3;36mAffiche la liste des demandes\e[0m\t\e[1;35m|\e[0m");
		printf("\n\e[1;35m________________________________________________________________________|\e[0m\n");
	}
	else
		printf("\e[1;34m________________________________________________________________________|\e[0m\n");
}

int invitation(unsigned long int idServ) {
	char *pseudo = strtok(NULL, " "); 
	unsigned long int idU = bdd_getUtilisateur_id(pseudo);
	
	if(bdd_check_membre(idServ,idU)){
		printf("\e[1;31m%s est deja membre de ce serveur\n\e[0m", pseudo);
		return 2;
	}
	
	if (idU == 0) {
		printf("\n\e[1;31m%s n'existe pas !\e[0m\n", pseudo);
		return 1;		
	}
	FILE * fichier=NULL;
	fichier = fopen("rsc/demande.dat","r");
	if(fichier==NULL)return -1;
	Demande demande;
	int size = bdd_getSize_table("demande");
	for(int i = 0; i < size;++i) {
		fread(&demande, sizeof(Demande), 1, fichier);
		if(demande.user_id == idU && demande.server_id == idServ) {
			bdd_creer_membre(idServ, idU, "Membre");
			printf("\e[1;32m%s est devenu membre du serveur\n\e[0m", pseudo);
			bdd_supprimer_invitation(idU, idServ);
			bdd_supprimer_demande(idU, idServ);
			fclose(fichier);
			return 0;		
		}
	}
	
	fclose(fichier);
	
	fichier = fopen("rsc/invitation.dat", "r");
	if(fichier==NULL)return -1;
	Invitation invitation;
	int size2= bdd_getSize_table("invitation");
	
	for(int i = 0; i < size2; ++i) {
		fread(&invitation, sizeof(Invitation), 1, fichier);
		
		if(invitation.user_id == idU && invitation.server_id == idServ) {
			printf("\e[1;31m%s à déjà été invité dans ce serveur\e[0m\n", pseudo);
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
		printf("\n\e[1;31m%s n'existe pas !\e[0m\n", pseudo);
		return 0;		
	}
	
	FILE *fichier = fopen("rsc/demande.dat", "r");
	Demande demande;
	
	for(int i = 0; i < bdd_getSize_table("demande") && fread(&demande, sizeof(Demande), 1, fichier) != EOF; ++i) {
		if(demande.user_id == idU && demande.server_id == idServ) {
			bdd_supprimer_demande(idU, idServ);
			bdd_creer_membre(idServ, idU, "Membre");
			printf("\n\e[1;32m%s est devenu membre du serveur\e[0m\n", pseudo);
			fclose(fichier);
			return 0;
		}
	}
	printf("\e[1;31mAucune demande de %s\e[0m\n", pseudo);
	fclose(fichier);
	return 0;
}

int createSalon(unsigned long int idServ) {
	char *nomSalon = strtok(NULL, " ");
	if(bdd_getSalon_id(idServ ,nomSalon) == 0) {
		if(bdd_create_Salon(nomSalon, idServ)==0){
			printf("\e[1;32m- Le salon '%s' a bien été crée\e[0m\n", nomSalon);
		};
	}
	else printf("\e[1;31mSalon déjà existant\e[0m\n");
	return 0;
}

int deleteSalon(unsigned long int idServ) {
	char *nomSalon = strtok(NULL, " ");
	
	unsigned long int idSalon= bdd_getSalon_id(idServ, nomSalon);
	
	if(idSalon != 0) {
		bdd_supprimer_salon(idSalon, idServ);
	}
	else printf("\e[1;31mSalon inexistant\e[0m\n");
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
	printf("\e[1;36mSalon[%d]\e[0m\n",getSalon(idServ));
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
		printf("\e[1;31mLe role %s n'existe pas\e[0m\n", nomRole);
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
		printf("\e[1;31m%s n'est pas membre du serveur\e[0m\n", pseudo);
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
						printf(">\e[33m%s\e[0m/\e[34m%s\e[0m $ ",utilisateur.pseudo,serveur.nom);
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
        if((perm.id_serveur==id_serveur && strcmp(perm.Role,monRole)==0 && perm.perms[1]=='x') || bdd_getProprietaireServeur_id(id_serveur)==id_user){  //si l'id correspond
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
	int i = 0;
	printf("\e[1;33mMembres[%d]\e[0m\n",getMembres(idServ));
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
					printf("\t\e[33m%s\e[0m : \e[34m%s\e[0m\n", utilisateur.pseudo, membre.role);
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
	int i = 0;
	
	while(i < size && fread(&perm, sizeof(Permissions_Serveur), 1, fichier) != EOF) 
	{	
		if(perm.id_serveur==idServ) 
		{
			printf("\e[1;34m%s\e[0m \t\e[1m[%s]\e[0m\n", perm.Role, perm.perms);
		
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
    	if(strlen(role)>30 || strlen(perm)!=2 || (perm[0]!='w' && perm[0]!='-') || (perm[1]!='x' && perm[1]!='-')){ //cas derreur
    		printf("\e[1;31mCommande invalide\e[0m\n");
    		return -1;
    	}
	int result = insert_perm_serveur(idServ, role, perm); //appel de la fonction pour attribuer les role de chacun au serv
	if (result==1){
		printf("\n\e[1;32mChangement de Permissions effectué \e[0m\n");
		printf("\n\e[3mNouvelles permissions\e[0m : \e[4m%s\e[0m \e[1m[%s]\e[0m\n\n", role, perm);
	}
	else if (result==0){
		printf("\n\e[1;32mCreation du role effectué \e[0m\n");
		printf("\n\e[3mNouveau role\e[0m : \e[4m%s\e[0m \e[1m[%s]\e[0m\n\n", role, perm);
	}
return 0;
}


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
	if(file2==NULL)return -1;
	rewind(file2); //mettre curseur au début du fichier

	while(fread(&perm,sizeof(Permissions_Serveur),1,file2) != EOF && i < size){   
		++i;
		if(perm.id_serveur==id_serveur && strcmp(perm.Role,Role)==0){  //si l'id correspond
		    fclose(file2);
		return 1;
		}
	   	if (i == bdd_getSize_table("permission_serveur")){
			fclose(file2);
			return 0; //Cas ou le role nexiste pas
		}
	}
	return 0;
}
