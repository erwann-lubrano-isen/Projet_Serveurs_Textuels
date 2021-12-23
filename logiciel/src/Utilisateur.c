#include "../headers/Utilisateur.h"

int bdd_creer_utilisateur(char pseudo[], char motDePasse[]){
	FILE * file = NULL;
	file = fopen("rsc/utilisateur.dat","r+");
	if(file == NULL) return -1;
	
	Utilisateur utilisateur;
	utilisateur.id=incrementeSerial("utilisateur");
	strcpy(utilisateur.pseudo , pseudo);
	strcpy(utilisateur.motDePasse, motDePasse);
	
	fseek(file, sizeof(Utilisateur)*(bdd_getSize_table("utilisateur")), SEEK_SET); //position du curseur a la fin de la table
	
	bdd_increment_table("utilisateur");  //augmente d'une place
	fwrite(&utilisateur,sizeof(Utilisateur),1,file);  //met la struc utilisateur dans le fichier, a la fin
	fclose(file);
	return 0;
	
}

int bdd_supprimer_utilisateur(unsigned long int id){
	//membre 
	supprimer_membres_parId(id);
	//demande
	bdd_supprimer_demande_parId(id);
	//invite
	bdd_supprimer_invitation_parId(id);
	//serveur
	bdd_supprimer_serveur_parId(id);
	
	
	
	int size = bdd_getSize_table("utilisateur");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("utilisateur");
		return 0;
	}
	int i =0;
	Utilisateur utilisateur;
	Utilisateur dernierUtilisateur; //struc user qui stockera le dernier pour le remplacer
	
	FILE * file = NULL;
	file = fopen("rsc/utilisateur.dat","r+");
	fseek(file,sizeof(Utilisateur)*(size-1),SEEK_SET); //mettre le curseur sur le dernier utilisateur
	fread(&dernierUtilisateur,sizeof(Utilisateur),1,file); //copie du dernier utilisateur(fichier) dans dernierUtilisateur

	rewind(file); //mettre curseur au début du fichier
	
	while(fread(&utilisateur,sizeof(Utilisateur),1,file) != EOF && i < size){   //read tant que la taille max du fichier est atteinte
		++i;
		if(utilisateur.id==id){  //si l'id correspond
			fseek(file,-sizeof(Utilisateur),SEEK_CUR);  //on repositione le curseur juste avant
			fwrite(&dernierUtilisateur,sizeof(Utilisateur),1,file); //on ecrase le membre par le dernier utilisateur
			if(size>=1){
				bdd_decrement_table("utilisateur");  //enfin, on decremente
				--size;  
			}
			--i;
			fseek(file,sizeof(Utilisateur)*(size-1),SEEK_SET);
			fread(&dernierUtilisateur,sizeof(Utilisateur),1,file);
			fseek(file,i*(sizeof(Utilisateur)),SEEK_SET);
		}
		
	}
	fclose(file); 
	return 0;
}

unsigned long int bdd_getUtilisateur_id(const char * nom){
	int size = bdd_getSize_table("utilisateur");
	int i =0;
	Utilisateur utilisateur;
	FILE * file = NULL;
	file = fopen("rsc/utilisateur.dat","r");
	while(fread(&utilisateur, sizeof(Utilisateur), 1, file) != EOF && i <= size){
		if(strcmp(utilisateur.pseudo,nom)==0){
			fclose(file);
			return utilisateur.id;
		}
		++i;
	}
	fclose(file);
	return 0;
}

void bdd_afficher_utilisateur(){
	int size = bdd_getSize_table("utilisateur");
	int i =0;
	Utilisateur utilisateur;
	FILE * file = NULL;
	file = fopen("rsc/utilisateur.dat","r");
	while(fread(&utilisateur,sizeof(Utilisateur),1,file) != EOF && i < size){
		printf("id_membre : %lu\tpseudo: %s\n",utilisateur.id, utilisateur.pseudo);
		++i;
	}
	fclose(file);
}


int bdd_getPseudo_utilisateur(char pseudo[], unsigned long int user_id){
	int size = bdd_getSize_table("utilisateur");
	FILE * file = fopen("rsc/utilisateur.dat","r");
	if(file==NULL)return -1;
	Utilisateur utilisateur;
	for(int i = 0;i < size;++i){
		fread(&utilisateur,sizeof(Utilisateur),1,file);
		if(user_id==utilisateur.id){
			strcpy(pseudo, utilisateur.pseudo);
			fclose(file);
			return 0;
		}
	}
	fclose(file);
	return 1;
}
