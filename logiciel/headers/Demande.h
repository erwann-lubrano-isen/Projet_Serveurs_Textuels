#ifndef __DEMANDE_H_
#define __DEMANDE_H_

typedef struct Demande{
	unsigned long int user_id;
	unsigned long int server_id;
}Demande;

int bdd_stock_demande(unsigned long int user_id, unsigned long int server_id);
int bdd_supprimer_demande(unsigned long int user_id, unsigned long server_id);
void bdd_afficher_demande();

#endif
