#include <string.h>
#include "../headers/Acceuil.h"

int acceuil() {
    char buffer[127];
    fgets(buffer, 127, stdin);
    char *commande = strtok(buffer, " ");
    if(!(strcmp(commande, "!help"))) return 1;
    if(!(strcmp(commande, "!create"))) return 2;
    if(!(strcmp(commande, "!join"))) return 3;
    if(!(strcmp(commande, "!quit"))) return 4;
    if(!(strcmp(commande, "!delete"))) return 5;
    if(!(strcmp(commande, "!listserver"))) return 6;
    if(!(strcmp(commande, "!listinvitation"))) return 7;
    if(!(strcmp(commande, "!accept"))) return 8;
    if(!(strcmp(commande, "!open"))) return 9;
    if(!(strcmp(commande, "!exit"))) return 10;
    if(!(strcmp(commande, "!logout"))) return 11;
    if(!(strcmp(commande, "!die"))) return 12;
    printf("%s: Action inexistante\n", commande);
    return -1;
}
