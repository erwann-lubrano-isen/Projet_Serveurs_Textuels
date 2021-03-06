#include "../headers/Membre.h"

int bdd_creer_membre(unsigned long int idServeur, unsigned long idUtilisateur, const char * role){
	FILE * file = NULL;
	file = fopen("rsc/membre.dat","r+");
	if(file==NULL)return -1;
	Membre membre;
	membre.idUtilisateur=idUtilisateur;
	membre.idServeur=idServeur;
	strcpy(membre.role,role);
	fseek(file, sizeof(Membre)*(bdd_getSize_table("membre")), SEEK_SET);
	fwrite(&membre,sizeof(Membre),1,file);
	fclose(file);
	file = NULL;
	bdd_increment_table("membre");
	return 0;
}
		
		
int bdd_check_membre(unsigned long int idServeur, unsigned long idUtilisateur){
	int size = bdd_getSize_table("membre");
	int i =0;
	Membre membre;
	FILE * file = NULL;
	file = fopen("rsc/membre.dat","r");
	while(fread(&membre,sizeof(Membre),1,file) != EOF && i < size){
		if(membre.idServeur==idServeur && membre.idUtilisateur==idUtilisateur){
			fclose(file);
			return 1;
		}
		++i;
	}
	fclose(file);
	return 0;
}

int bdd_supprimer_membre(unsigned long int idServeur, unsigned long idUtilisateur){
	int size = bdd_getSize_table("membre");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("membre");
		return 0;
	}
	int i =0;
	Membre membre;
	Membre dernierMembre;
	FILE * file = NULL;
	file = fopen("rsc/membre.dat","r+");
	fseek(file,sizeof(Membre)*(size-1),SEEK_SET);
	fread(&dernierMembre,sizeof(Membre),1,file);
	fseek(file,0,SEEK_SET);
	while(fread(&membre,sizeof(Membre),1,file) != EOF && i < size){
		++i;
		if(membre.idServeur==idServeur && membre.idUtilisateur==idUtilisateur){
			fseek(file,-sizeof(Membre),SEEK_CUR);
			fwrite(&dernierMembre,sizeof(Membre),1,file);
			if(size>=1){
				bdd_decrement_table("membre");
				--size;
			}
			--i;
			fseek(file,sizeof(Membre)*(size-1),SEEK_SET);
			fread(&dernierMembre,sizeof(Membre),1,file);
			fseek(file,i*(sizeof(Membre)),SEEK_SET);
		}
		
	}
	fclose(file);
	return 0;
}

void bdd_afficher_membres(){
	int size = bdd_getSize_table("membre");
	int i =0;
	Membre membre;
	FILE * file = NULL;
	file = fopen("rsc/membre.dat","r");
	while(fread(&membre,sizeof(Membre),1,file) != EOF && i < size){
		printf("id_serveur : %lu\tid_user: %lu\n",membre.idServeur,membre.idUtilisateur);
		++i;
	}
	fclose(file);
}

int supprimer_membres_serveur(unsigned long int idServeur){
	int size = bdd_getSize_table("membre");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("membre");
		return 0;
	}
	int i =0;
	Membre membre;
	Membre dernierMembre;
	FILE * file = NULL;
	file = fopen("rsc/membre.dat","r+");
	fseek(file,sizeof(Membre)*(size-1),SEEK_SET);
	fread(&dernierMembre,sizeof(Membre),1,file);
	fseek(file,0,SEEK_SET);
	while(fread(&membre,sizeof(Membre),1,file) != EOF && i < size){
		++i;
		if(membre.idServeur==idServeur){
			fseek(file,-sizeof(Membre),SEEK_CUR);
			fwrite(&dernierMembre,sizeof(Membre),1,file);
			if(size>=1){
				bdd_decrement_table("membre");
				--size;
			}
			--i;
			fseek(file,sizeof(Membre)*(size-1),SEEK_SET);
			fread(&dernierMembre,sizeof(Membre),1,file);
			fseek(file,i*(sizeof(Membre)),SEEK_SET);
		}
		
	}
	fclose(file);
	return 0;
}
int supprimer_membres_parId(unsigned long int id_user){
	int size = bdd_getSize_table("membre");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("membre");
		return 0;
	}
	int i =0;
	Membre membre;
	Membre dernierMembre;
	FILE * file = NULL;
	file = fopen("rsc/membre.dat","r+");
	fseek(file,sizeof(Membre)*(size-1),SEEK_SET);
	fread(&dernierMembre,sizeof(Membre),1,file);
	fseek(file,0,SEEK_SET);
	while(fread(&membre,sizeof(Membre),1,file) != EOF && i < size){
		++i;
		if(membre.idUtilisateur==id_user){
			fseek(file,-sizeof(Membre),SEEK_CUR);
			fwrite(&dernierMembre,sizeof(Membre),1,file);
			if(size>=1){
				bdd_decrement_table("membre");
				--size;
			}
			--i;
			fseek(file,sizeof(Membre)*(size-1),SEEK_SET);
			fread(&dernierMembre,sizeof(Membre),1,file);
			fseek(file,i*(sizeof(Membre)),SEEK_SET);
		}
		
	}
	fclose(file);
	return 0;
}

int role(unsigned long int userid, unsigned long int id_serveur){
	char *rolename = strtok(NULL, " "); 
	if(rolename==NULL || strlen(rolename)>40 || strlen(rolename) > 40){
		printf("commande incorrecte\n");
		return 1;
	}
	FILE * fichier;
	Membre membre;
	fichier = fopen("rsc/membre.dat","r");
	int size = bdd_getSize_table("Membre");
	int i=0;
	if(fichier == NULL)return -1;
	while(fread(&membre,sizeof(Membre),1,fichier)!=EOF&&i<size){
		if(userid == membre.idUtilisateur && id_serveur ==membre.idServeur ){
			printf("role deja attribu?? !\n");
			fseek(fichier,-sizeof(Membre),SEEK_CUR);
			fwrite(&membre,sizeof(Membre),1,fichier);
			fclose(fichier);
			return 0;
		}
		++i;
		
	}
	fclose(fichier);
	//bd_creationServeur(servname,idProprio);
	//bdd_creer_membre(bdd_getServeur_id(servname), idProprio, "Admin");
	return 0;
}

int bdd_getRole_membre(char role[], unsigned long int user_id, unsigned long int id_serveur){
	int size = bdd_getSize_table("membre");
	FILE * file = fopen("rsc/membre.dat","r");
	if(file==NULL)return -1;
	Membre membre;
	for(int i = 0;i < size;++i){
		fread(&membre,sizeof(Membre),1,file);
		if(user_id==membre.idUtilisateur && id_serveur == membre.idServeur){
			strcpy(role, membre.role);
			fclose(file);
			return 0;
		}
	}
	fclose(file);
	return 1;
}


