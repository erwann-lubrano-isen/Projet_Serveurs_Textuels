/**
* @author Erwann.L, Lilian.D, Lucas.B, Jordan.P
*/

#include <stdio.h>

#include "headers/MenuSalon.h"
#include "headers/Serveur.h"
#include "headers/Salon.h"
#include "headers/Utilisateur.h"
#include "headers/Connexions_Action.h"


int fileMissing();
void reset();


int main() {
	if(fileMissing())reset();
	menuConnexion();
	return 0;
}

int fileMissing(){
	FILE * file = NULL;
	
	file = fopen("rsc/serveur.dat","r");
	if(file==NULL)return 1;
	fclose(file);
	
	file = fopen("rsc/utilisateur.dat","r");
	if(file==NULL)return 1;
	fclose(file);
	
	file = fopen("rsc/membre.dat","r");
	if(file==NULL)return 1;
	fclose(file);
	
	file = fopen("rsc/salon.dat","r");
	if(file==NULL)return 1;
	fclose(file);
	
	file = fopen("rsc/permission_salon.dat","r");
	if(file==NULL)return 1;
	fclose(file);
	
	file = fopen("rsc/permission_serveur.dat","r");
	if(file==NULL)return 1;
	fclose(file);
	
	file = fopen("rsc/message.dat","r");
	if(file==NULL)return 1;
	fclose(file);
	
	file = fopen("rsc/invitation.dat","r");
	if(file==NULL)return 1;
	fclose(file);
	
	file = fopen("rsc/demande.dat","r");
	if(file==NULL)return 1;
	fclose(file);
	
	file = fopen("rsc/table.dat","r");
	if(file==NULL)return 1;
	fclose(file);
	
	file = fopen("rsc/serial.dat","r");
	if(file==NULL)return 1;
	fclose(file);
	
	return 0;
}


void reset(){
	FILE * file = NULL;
	file = fopen("rsc/serveur.dat","w");
	fclose(file);
	file = fopen("rsc/utilisateur.dat","w");
	fclose(file);
	file = fopen("rsc/membre.dat","w");
	fclose(file);
	file = fopen("rsc/salon.dat","w");
	fclose(file);
	file = fopen("rsc/permission_salon.dat","w");
	fclose(file);
	file = fopen("rsc/permission_serveur.dat","w");
	fclose(file);
	file = fopen("rsc/message.dat","w");
	fclose(file);
	file = fopen("rsc/invitation.dat","w");
	fclose(file);
	file = fopen("rsc/demande.dat","w");
	fclose(file);
	
	file = fopen("rsc/table.dat","w");
	Table table[11] = {
						{"serveur",0},
						{"utilisateur",0},
						{"membre",0},
						{"salon",0},
						{"permission_salon",0},
						{"permission_serveur",0},
						{"message",0},
						{"invitation",0},
						{"demande",0},
						{"serial",3},
						{"table",11}};
	fwrite(table,sizeof(Table),11,file);
	fclose(file);
	
	file = fopen("rsc/serial.dat","w");
	Serial serials[3]={
		{"serveur","id",1},
		{"utilisateur","id",1},
		{"salon","id",1}};
	fwrite(serials,sizeof(Serial),3,file);
	fclose(file);
}
