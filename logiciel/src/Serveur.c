#include "../headers/Serveur.h"


int bd_creationServeur(const char * const nom, unsigned long int idProprio) {

	Serveur serveur;
	strcpy(serveur.nom, nom);	//Initialisation de serveur 
	serveur.idProprio = idProprio;
	serveur.id = incrementeSerial("serveur"); //Incrementation de serial
	
	FILE *fichier;
	fichier = fopen("rsc/serveur.dat", "r+"); //Ouverture de fichier
	if(fichier == NULL) return -1; //Vérification d'erreur
	//** mettre l'utilisateur qui cree le serveur, "administrateur", dans role de membre, donc ça cree le 1er membre du serveur
	
	insert_perm_serveur(serveur.id, "Admin", "wx");
	insert_perm_serveur(serveur.id, "Membre", "--");
	fseek(fichier, sizeof(Serveur)*(bdd_getSize_table("serveur")), SEEK_SET);
	bdd_increment_table("serveur");
	fwrite(&serveur, sizeof(Serveur), 1, fichier);
	fclose(fichier);
	return 0;
}

int bd_suppressionServeur(unsigned long int id) {

	FILE *fichier = fopen("rsc/serveur.dat", "r+");
	if (fichier == NULL) return -1;
	
	Serveur serveur;
	
	for(int i = 1; i < bdd_getSize_table("serveur") && fread(&serveur, sizeof(Serveur), 1, fichier) != EOF; ++i) {
		if (serveur.id == id) {
			fseek(fichier, sizeof(Serveur)*(bdd_getSize_table("serveur")-1), SEEK_SET); //Positionnement du curseur au début de la dernière ligne
			fread(&serveur, sizeof(Serveur), 1, fichier);	//Obtention de la dernière ligne dans serveur
			fseek(fichier, sizeof(Serveur)*(i-1), SEEK_SET); //Positionnement au début de la ligne i
			fwrite(&serveur, sizeof(Serveur), 1, fichier);	//Ecriture de la dernière ligne contenue dans serveur
			bdd_decrement_table("serveur");
			return 0;
		}
	}
	fclose(fichier);
	return 0;
}
int bdd_supprimer_serveur_parId(unsigned long int user_id){
	int size = bdd_getSize_table("serveur");
	if(size==0)return 0;
	int i =0;
	Serveur serveur;
	Serveur dernierServeur;
	FILE * file = NULL;
	file = fopen("rsc/serveur.dat","r+");
	fseek(file,sizeof(Serveur)*(size-1),SEEK_SET);
	fread(&dernierServeur,sizeof(Serveur),1,file);
	fseek(file,0,SEEK_SET);

	while(fread(&serveur,sizeof(Serveur),1,file) != EOF && i < size){
		++i;

		if(serveur.idProprio==user_id){
			fseek(file,-sizeof(Serveur),SEEK_CUR);
			fwrite(&dernierServeur,sizeof(Serveur),1,file);
			if(size>=1){
				bdd_decrement_table("serveur");
				--size;
			}
			
			--i;
			fseek(file,sizeof(Serveur)*(size-1),SEEK_SET);
			fread(&dernierServeur,sizeof(Serveur),1,file);
			fseek(file,i*(sizeof(Serveur)),SEEK_SET);
		}
		
	}
	fclose(file);
	
	return 0;
}


int bd_suppressionMembresEtServeur(unsigned long int id) {
	bd_suppressionServeur(id);
	supprimer_membres_serveur(id);
	supprimer_salons_serveur(id);
	return 0;
}

unsigned long int bdd_getServeur_id(const char * nom){
	int size = bdd_getSize_table("serveur");
	int i =0;
	Serveur serveur;
	FILE * file = NULL;
	file = fopen("rsc/serveur.dat","r");
	while(fread(&serveur,sizeof(Serveur),1,file) != EOF && i <= size){
		if(strcmp(serveur.nom,nom)==0){
			fclose(file);
			return serveur.id;
		}
		++i;
	}
	fclose(file);
	return 0;
}

unsigned long int bdd_getProprietaireServeur_id(unsigned long int serveur_id){
	int size = bdd_getSize_table("serveur");
	int i =0;
	Serveur serveur;
	FILE * file = NULL;
	file = fopen("rsc/serveur.dat","r");
	while(fread(&serveur,sizeof(Serveur),1,file) != EOF && i <= size){
		if(serveur.id==serveur_id){
			fclose(file);
			return serveur.idProprio;
		}
		++i;
	}
	fclose(file);
	return 0;
}

void bdd_afficher_serveurs(){
	int size = bdd_getSize_table("serveur");
	int i =0;
	Serveur serveur;
	FILE * file = NULL;
	file = fopen("rsc/serveur.dat","r");
	while(fread(&serveur,sizeof(Serveur),1,file) != EOF && i < size){
		printf("id_serveur : %lu\tid_user: %lu\tnom : %s\n",serveur.id,serveur.idProprio,serveur.nom);
		++i;
	}
	fclose(file);
}


