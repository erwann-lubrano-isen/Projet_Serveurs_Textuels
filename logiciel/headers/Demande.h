#ifndef __DEMANDE_H_
#define __DEMANDE_H_

/**
* @struct Demande
* @brief demande d'un utilisateur pour rejoindre un serveur
*/
typedef struct Demande{
	unsigned long int user_id;
	unsigned long int server_id;
}Demande;

/**
* @brief cree une demande
* @param user_id : id de l'utilisateur
* @param server_id : id du serveur
*/
int bdd_stock_demande(unsigned long int user_id, unsigned long int server_id);

/**
* @brief supprime une demande
* @param user_id : id de l'utilisateur
* @param server_id : id du serveur
*/
int bdd_supprimer_demande(unsigned long int user_id, unsigned long server_id);

/**
* @brief affiche la liste des demandes
*/
void bdd_afficher_demande();

/**
* @brief supprime toutes les demandes faites par un utilisateur
* @param user_id : id de l'utilisateur
*/
int bdd_supprimer_demande_parId(unsigned long int user_id);

#endif
