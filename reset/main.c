#include "../logiciel/headers/Table.h"
#include "../logiciel/headers/Serial.h"
#include <stdio.h>

int main(){
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
		{"serveur","id",0},
		{"utilisateur","id",0},
		{"salon","id",0}};
	fwrite(serials,sizeof(Serial),3,file);
	fclose(file);
	return 0;
}