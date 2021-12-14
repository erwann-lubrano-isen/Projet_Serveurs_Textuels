#include "../headers/Message.h"

int bdd_creer_message(unsigned long int id_salon, unsigned long int id_utilisateur, time_t date, char texte[]){
	FILE * file = NULL;
	file = fopen("rsc/message.dat","a");
	if(file == NULL)return -1;
	Message message;
	message.id_salon = id_salon;
	message.id_utilisateur = id_utilisateur;
	message.date = date;
	memcpy(message.texte,texte,(strlen(texte)<120)?strlen(texte):120);
	fwrite(&message,sizeof(Message),1,file);
	fclose(file);
	file = NULL;
	bdd_increment_table("message");
}