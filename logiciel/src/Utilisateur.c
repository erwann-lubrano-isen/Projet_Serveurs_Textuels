#include "../headers/Utilisateur.h"

int bdd_creer_utilisateur(char pseudo[], char motDePasse[]){
	FILE * file = NULL;
	file = fopen("rsc/utilisateur.dat","a");
	
	Utilisateur utilisateur;
	utilisateur.id=incrementSerial("utilisateur");
	strcpy(utilisateur.pseudo , pseudo);
	strcpy(utilisateur.motDePasse, motDePasse);
	
	fwrite(&utilisateur,sizeof(Utilisateur),1,file);  //met la struc utilisateur dans le fichier
	fclose(file);
	
	bdd_increment_table("utilisateur");
}

int bdd_supprimer_utilisateur(unsigned long int id){
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
	file = fopen("rsc/Utilisateur.dat","r+");
	fseek(file,sizeof(Utilisateur)*(size-1),SEEK_SET); //mettre le curseur sur le dernier utilisateur
	fread(&dernierUtilisateur,sizeof(Utilisateur),1,file); //copie du dernier utilisateur(fichier) dans dernierUtilisateur
	
	rewind(file); //mettre curseur au début du fichier
	
	while(fread(&utilisateur,sizeof(Utilisateur),1,file) != EOF && i < size){   //read tant que la taille max du fichier est atteinte
		++i;
		if(utilisateur.id==id){  //si l'id correspond
			fseek(file,-sizeof(Utilisateur),SEEK_CUR);  //on repositione le curseur juste avant
			fwrite(&dernierMembre,sizeof(Membre),1,file); //on ecrase le membre par le dernier utilisateur
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
