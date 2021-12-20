#include "../headers/Message.h"

int bdd_creer_message(unsigned long int id_salon, unsigned long int id_utilisateur, time_t date, const char * const texte){
	FILE * file = NULL;
	file = fopen("rsc/message.dat","r+");
	if(file == NULL)return -1;
	Message message;
	message.id_salon = id_salon;
	message.id_utilisateur = id_utilisateur;
	message.date = date;
	strcpy(message.texte,texte);
	fseek(file, sizeof(Message)*(bdd_getSize_table("message")), SEEK_SET);
	fwrite(&message,sizeof(Message),1,file);
	fclose(file);
	file = NULL;
	bdd_increment_table("message");
}

void bdd_afficherMessages(){
	int size = bdd_getSize_table("message");
	int i =0;
	Message message;
	FILE * file = NULL;
	file = fopen("rsc/message.dat","r");
	while(fread(&message,sizeof(Message),1,file) != EOF && i < size){
		printf("user : %lu\tsalon : %lu\t%s\n%s\n\n",message.id_utilisateur, message.id_salon,ctime(&message.date),message.texte);
		++i;
	}
	fclose(file);
}

int bdd_supprimer_message(unsigned long int id_salon, unsigned long int id_utilisateur, time_t date){
	int size = bdd_getSize_table("message");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("message");
		return 0;
	}
	int i =0;
	Message message;
	Message dernierMessage;
	FILE * file = NULL;
	file = fopen("rsc/message.dat","r+");
	fseek(file,sizeof(Message)*(size-1),SEEK_SET);
	fread(&dernierMessage,sizeof(Message),1,file);
	fseek(file,0,SEEK_SET);
	while(fread(&message,sizeof(Message),1,file) != EOF && i < size){
		++i;
		if(message.id_salon==id_salon && message.id_utilisateur==id_utilisateur,message.date=date){
			fseek(file,-sizeof(Message),SEEK_CUR);
			fwrite(&dernierMessage,sizeof(Message),1,file);
			if(size>=1){
				bdd_decrement_table("membre");
				--size;
			}
			--i;
			fseek(file,sizeof(Message)*(size-1),SEEK_SET);
			fread(&dernierMessage,sizeof(Message),1,file);
			fseek(file,i*(sizeof(Message)),SEEK_SET);
		}
		
	}
	fclose(file);
	return 0;
}
