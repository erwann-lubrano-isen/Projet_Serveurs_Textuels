#include "../headers/Acceuil_Actions.h"

int menuAcceuil(unsigned long int user_id){
	char buffer[128];
    
    do{
    	fgets(buffer, 127, stdin);
    	int lenght = strlen(buffer);
    	buffer[lenght-1]=' ';
    	buffer[lenght]='\0';
    	char *commande = strtok(buffer, " ");
    	
    	if(!(strcmp(commande, "!help")));
		else if(!(strcmp(commande, "!back")))return 1;
    	else if(!(strcmp(commande, "!exit"))) return 0;
    	else printf("Action inexistante\n");
    }while(1);    
    return 0;
}
