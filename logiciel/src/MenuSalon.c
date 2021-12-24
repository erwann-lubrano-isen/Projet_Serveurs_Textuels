#include "../headers/MenuSalon.h"


int menuSalon(unsigned long int id_salon, unsigned long int id_utilisateur, unsigned long int id_serveur) {
	int permR_salon=readPerm(id_salon, id_utilisateur);
	int permW_salon=bdd_hasWPerm_salon(id_salon, id_utilisateur);
	int permX_serveur=bdd_hasXPerm_serveur(id_serveur, id_utilisateur);
    char buffer[128];
    if (checkRole(id_utilisateur, id_salon, id_serveur)==1){
    	printf("\e[1;31mVous n'avez pas le droit d'accès a ce serveur\e[0m\n");
    	return 1;
    }
    do{
			prompt_salon(id_utilisateur, id_serveur,  id_salon);
			fgets(buffer, 127, stdin);
			if(buffer[0]==' '){
				printf("\e[1;31Action inexistante\e[0m\n");
				continue;
			}
			int lenght = strlen(buffer); 
			if(lenght<=1)continue;    
			buffer[lenght-1]=' ';
			buffer[lenght]='\0';
			//&& isAdmin(id_utilisateur, id_serveur)
			char *commande = strtok(buffer, " ");
			if(!(strcmp(commande, "help"))) helpSalon(id_utilisateur, id_serveur);
			else if((strcmp(commande, "perm")==0 || strcmp(commande, "chmod")==0) && permX_serveur == 1){
				permSalon(id_salon, id_serveur);// if isAdmin(id_user, id_serveur)==1
				permR_salon=readPerm(id_salon, id_utilisateur);
				permW_salon=bdd_hasWPerm_salon(id_salon, id_utilisateur);
				permX_serveur=bdd_hasXPerm_serveur(id_serveur, id_utilisateur);
			}else if((strcmp(commande, "msg")==0) && permW_salon == 1) msgSalon(id_salon, id_utilisateur);
			else if(!(strcmp(commande, "exit"))){
		        	auRevoir(id_utilisateur);
		        	return 0;
		        }
			else if(!(strcmp(commande, "role"))) permMembresSalon(id_salon);
			else if((strcmp(commande, "back")==0) || (strcmp(commande, "cd..")==0)) return 1;
			else if((strcmp(commande, "display")==0 || strcmp(commande, "ls")==0) && permR_salon == 1) displayMsg(id_utilisateur, id_serveur, id_salon);
			
			else printf("%s: \e[1;31Action inexistante\e[0m\n", commande);
	}while(checkRole(id_utilisateur, id_salon, id_serveur)==0);
	
return 1;
}

void helpSalon(unsigned long int id_utilisateur, unsigned long int id_serveur){
	printf("\e[1;34m---------------------[LISTE DES COMMANDES]---------------------\t|\e[0m\n");
	printf("\t\t\t\t\t\t\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mmsg 'text'\e[0m\t\e[1;5m----->\e[0m\t\e[3;36mEnvoyer un message[w]\e[0m\t\t\e[1;34m|\e[0m\n"); 
	printf("\t\e[4;40;33mdisplay\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mAfficher tout les messages[r]\e[0m\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mrole\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mVoir les roles du salons\e[0m\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mback\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mRetour en arrière\e[0m\t\t\e[1;34m|\e[0m\n");
	printf("\t\e[4;40;33mexit\e[0m\t\t\e[1;5m----->\e[0m\t\e[3;36mQuitter le programme\e[0m\t\t\e[1;34m|\e[0m\n");
	printf("\t\t\t\t\t\t\t\t\e[1;34m|\e[0m\e[0m\n");
	if (isAdmin(id_utilisateur, id_serveur)){
		printf("\e[1;35m-----------------------[ADMINISTRATION]------------------------\t|\e[0m\n");
		printf("\t\t\t\t\t\t\t\t\e[1;35m|\e[0m\n");		
		printf("\t\e[4;40;33mperm 'rolename' 'perm'\e[0m\t\e[1;5m---->\e[0m\t\e[3;36mCrée/Modifier un role\e[0m\t\e[1;35m|\e[0m");
		printf("\n\e[1;35m________________________________________________________________|\e[0m\n");
	}
	else
		printf("\e[1;34m________________________________________________________________|\e[0m\n");
}


int permSalon(unsigned long int id_salon, unsigned long int id_serveur){
	char *role = strtok(NULL, " ");
	char *perm = strtok(NULL, " ");
	if(role==NULL||perm==NULL)return -1;
	if(strlen(role)>30 || strlen(perm)!=2 || (perm[0]!='r' && perm[0]!='-') || (perm[1]!='w' && perm[1]!='-')){ //cas derreur
		printf("\e[1;31mCommande invalide\e[0m\n");
		return -1;
	}
	insert_perm_salon(id_salon, role, perm); //appel de la fonction pour attribuer les role de chacun a un salon
	if (checkRoleServ( id_serveur, role)==0){
		insert_perm_serveur(id_serveur, role, "--");
	}
	return 0;
}

int msgSalon(unsigned long int id_salon, unsigned long int id_utilisateur){
	char *texte = strtok(NULL, "\0");  // phrase envoyé par l'utilisateur, s'arrête au \n qui signifie le dernier caractere
	if (texte == NULL || strlen(texte)>120){ //cas d'érreur
		printf("\e[1;31mMessage invalide\e[0m\n");
		return -1;
	}
	time_t date=time(NULL); // date = date actuel
	bdd_creer_message(id_salon, id_utilisateur, date, texte); //fonction de Message pour crée un message
	return 0;
}



int displayMsg(unsigned long int id_utilisateur, unsigned long int id_serveur, unsigned long int id_salon){
	int sizeMessage = bdd_getSize_table("message");
	Message message;
	int nbMessage=0;
	{
		int c =0;
		FILE * file3 = NULL;
		file3 = fopen("rsc/message.dat","r");
		while(fread(&message, sizeof(Message), 1, file3) != EOF && c < sizeMessage){
			if(message.id_salon==id_salon){
				++nbMessage;
			}
			++c;
		}
		fclose(file3);
	}
	Message msgs[nbMessage];
	nbMessage=0;
	{
		int c =0;
		FILE * file3 = NULL;
		file3 = fopen("rsc/message.dat","r");
		while(fread(&message, sizeof(Message), 1, file3) != EOF && c < sizeMessage){
			if(message.id_salon==id_salon){
				memcpy(&msgs[nbMessage],&message,sizeof(Message));
				++nbMessage;
			}
			++c;
		}
		fclose(file3);
	}
	
	for(Message * it = msgs;it < msgs+nbMessage-1;++it){
		for(Message * jt = it+1;jt < msgs+nbMessage;++jt){
			if(it->date > jt->date){
				time_t date = jt->date;
				jt->date = it->date;
				it->date=date;
			}
		}
	}
	
	char pseudo[30];
	if(bdd_getPseudo_utilisateur(pseudo, id_utilisateur)==-1)return -1;
	
	for(Message * msg = msgs;msg < msgs+nbMessage;++msg){
		Utilisateur utilisateur;
		
		int user_found=0;
		int size_utilisateur=bdd_getSize_table("utilisateur");
		FILE * file = NULL;
		file = fopen("rsc/utilisateur.dat","r");
		for(int i=0;i < size_utilisateur;++i){
			fread(&utilisateur,sizeof(Utilisateur),1,file);
			if(utilisateur.id==msg->id_utilisateur){
				user_found=1;
				break;
			}
		}
		fclose(file);
		const char * couleur = "\033[0m";
		if(strstr(msg->texte, pseudo)){
			couleur = "\033[1;45m";
		}
		if(user_found){
			fprintf(stdout,"%s : %s  %s%s\033[0m\n\n", utilisateur.pseudo,ctime(&msg->date), couleur ,msg->texte);
		}else{
			fprintf(stdout,"Anonyme : %s%s%s\033[0m\n\n", ctime(&msg->date),couleur, msg->texte);
		}
		
	}
	return 0;
}
void permMembresSalon(unsigned long int idSalon) {

	int size = bdd_getSize_table("permission_salon");
	FILE *fichier = fopen("rsc/permission_salon.dat", "r");
	Permissions_Salon perm;
	int i = 0;
	
	while(i < size && fread(&perm, sizeof(Permissions_Salon), 1, fichier) != EOF) 
	{	
		if(perm.id_salon==idSalon) 
		{
			printf("\t\e[1;34m%s\e[0m \t\e[1m[%s]\e[0m\n", perm.Role, perm.perms);
		
		}
	i++;
	}
	fclose(fichier);
}
void prompt_salon(unsigned long int user_id, unsigned long int serveur_id, unsigned long int idSalon){
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
						int size3 = bdd_getSize_table("salon");
						int x =0;
						Salon salon;
						FILE * file3 = NULL;
						file3 = fopen("rsc/salon.dat","r");
						while(fread(&salon, sizeof(Salon), 1, file3) != EOF && x <= size3){
							if(idSalon==salon.idSalon){
						
								printf(">\e[33m%s\e[0m/\e[34m%s\e[0m/\e[36m%s\e[0m $ ",utilisateur.pseudo,serveur.nom,salon.nom);
								fclose(file);
								fclose(file2);
								fclose(file3);
								return;
							}x++;
						}
					fclose(file3);
					}
					++j;
				}
				fclose(file2);
		}
		++i;
	}
fclose(file);
}

int checkRole(unsigned long int id_user, unsigned long int id_salon, unsigned long int id_serveur){
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
    size = bdd_getSize_table("permission_salon");
    if(size==0)return 0;
    i =0;
    Permissions_Salon perm;
    
    FILE * file2 = NULL;
    file2 = fopen("rsc/permission_salon.dat","r");

    rewind(file2); //mettre curseur au début du fichier
    
    while(fread(&perm,sizeof(Permissions_Salon),1,file2) != EOF && i < size){   //read tant que la taille max du fichier est atteinte
        ++i;
        if(perm.id_salon==id_salon && strcmp(perm.Role,monRole)==0 ){  //si l'id correspond
            if(perm.perms[0]=='r'){
            fclose(file2);
            return 0;
            }
            else{
            fclose(file2);
            return 1;
            }
        }
    }
    fclose(file2);
    insert_perm_salon(id_salon, monRole, "rw");
    return 0;        
}
/*
unsigned long int id_salon;
	unsigned long int id_utilisateur;
	time_t date;
	char texte[120];*/
