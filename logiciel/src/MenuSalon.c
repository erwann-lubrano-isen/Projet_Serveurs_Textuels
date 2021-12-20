#include "../headers/MenuSalon.h"


int menuSalon(unsigned long int id_salon, unsigned long int id_utilisateur, unsigned long int id_serveur) {
    char buffer[128];
    memset(buffer,'\0',128);
    do{
    	prompt_salon(id_utilisateur, id_serveur,  id_salon);
    	fgets(buffer, 127, stdin);
    	if(buffer[0]==' '){
    		printf("Action inexistante\n");
    		continue;
    	}
    	int lenght = strlen(buffer); 
    	if(lenght<=1)continue;    
    	buffer[lenght-1]=' ';
    	buffer[lenght]='\0';
    	//&& isAdmin(id_utilisateur, id_serveur)
    	char *commande = strtok(buffer, " ");
    	if(!(strcmp(commande, "help"))) helpSalon();
    	else if(strcmp(commande, "perm")==0 || strcmp(commande, "chmod")==0 /*&& isAdmin(id_utilisateur, id_serveur)*/) permSalon(id_salon);// if isAdmin(id_user, id_serveur)==1
    	else if(!(strcmp(commande, "msg"))) msgSalon(id_salon, id_utilisateur);
    	else if(!(strcmp(commande, "exit"))) return 0;
    	else if(!(strcmp(commande, "role"))) permMembresSalon(id_salon);
    	else if((strcmp(commande, "back")==0) || (strcmp(commande, "cd..")==0)) return 1;
    	else if((strcmp(commande, "display")==0) || (strcmp(commande, "ls")==0)) displayMsg(id_utilisateur, id_serveur, id_salon);
    	
    	else printf("%s: Action inexistante\n", commande);
    }while(1);
}

void helpSalon(){
	printf("-------------Voici la liste des commandes--------------\n");
	printf("!perm rolename perm :  Change les droits pour le salon\n"); // if (isAdmin(id_user, id_serveur))
	printf("!msg text: Envoyer un message\n");
	printf("!role : Voir les roles du salons\n");
	printf("!exit : Quitter le programme\n");
	printf("!back : Retur en arrière\n");
	printf("!display : Afficher tout les messages\n");
}

int permSalon(unsigned long int id_salon){
	char *role = strtok(NULL, " ");
	char *perm = strtok(NULL, " ");
	if(role==NULL||perm==NULL)return -1;
	printf("\nlongueur de perm %lu\n", strlen(perm));
	printf("\n\n%s : %c%c\n", role, perm[0],perm[1]);
	if(strlen(role)>30 || strlen(perm)!=2 || perm[0]!='r' && perm[0]!='-' || perm[1]!='w' && perm[1]!='-'){ //cas derreur
		printf("Commande invalide\n");
		return -1;
	}
	insert_perm_salon(id_salon, role, perm); //appel de la fonction pour attribuer les role de chacun a un salon
	return 0;
}

int msgSalon(unsigned long int id_salon, unsigned long int id_utilisateur){
	char *texte = strtok(NULL, "\0");  // phrase envoyé par l'utilisateur, s'arrête au \n qui signifie le dernier caractere
	if (texte == NULL || strlen(texte)>120){ //cas d'érreur
		printf("Message invalide\n");
		return -1;
	}
	time_t date=time(NULL); // date = date actuel
	bdd_creer_message(id_salon, id_utilisateur, date, texte); //fonction de Message pour crée un message
	return 0;
}



int displayMsg(unsigned long int id_utilisateur, unsigned long int id_serveur, unsigned long int id_salon){
	if(!readPerm(id_salon,id_utilisateur))return 1;
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
		fclose(file);/*
		char * carac = strchr(msg->texte,'\n');
		if(carac != NULL)*carac='\0';
		carac= strrchr(msg->texte,'');
		if(carac != NULL)*carac='\0';
		carac= strrchr(msg->texte,'');
		if(carac != NULL)*carac='\0';
		carac= strrchr(msg->texte,0xD0);
		if(carac != NULL)*carac='\0';
		carac= strrchr(msg->texte,0xEF);
		if(carac != NULL)*carac='\0';
		carac= strrchr(msg->texte,0xD9);
		if(carac != NULL)*carac='\0';
		carac= strrchr(msg->texte,0xFD);
		if(carac != NULL)*carac='\0';
		carac= strrchr(msg->texte,0xCD);
		if(carac != NULL)*carac='\0';
		*/
		if(user_found){
			fprintf(stdout,"%s : %s\n%s\n",utilisateur.pseudo,ctime(&msg->date),msg->texte);
		}else{
			fprintf(stdout,"Anonyme : %s\n%s\n",ctime(&msg->date),msg->texte);
		}
		
	}

}
void permMembresSalon(unsigned long int idSalon) {

	int size = bdd_getSize_table("permission_salon");
	FILE *fichier = fopen("rsc/permission_salon.dat", "r");
	Permissions_Salon perm;
	char nomRole[30];
	int i = 0;
	
	while(i < size && fread(&perm, sizeof(Permissions_Salon), 1, fichier) != EOF) 
	{	
		if(perm.id_salon==idSalon) 
		{
			printf("%s [%s]\n", perm.Role, perm.perms);
		
		}
	i++;
	}
	fclose(fichier);
	return;
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
						
								printf(">%s/%s/%s $ ",utilisateur.pseudo,serveur.nom,salon.nom);
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
/*
unsigned long int id_salon;
	unsigned long int id_utilisateur;
	time_t date;
	char texte[120];*/
