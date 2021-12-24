#ifndef __SALON_H_
#define __SALON_H_

#include <stdio.h>
#include "Table.h"
#include "Serial.h"
#include "Permissions_Salon.h"

/**
* @struct Salon
* @brief salon textuel
*/
typedef struct Salon {
	unsigned long int idSalon;
	unsigned long int idServeur;
	char nom[30];
}Salon;

/**
* @brief vérifie si un salon existe déjà
* @param idSalon : id du salon
* @param idServeur : id du serveur
* @return 1:true 0:false
*/
int bdd_Salon_check(unsigned long int idSalon, unsigned long int idServeur);

/**
* @brief créer un salon
* @param nom : nom du salon
* @param idServeur : id du serveur
*/
int bdd_create_Salon(char nom[], unsigned long int idServeur);

/**
* affiche tous les salons
*/
void bdd_afficher_salon();

/**
* @brief supprime un salon
* @param idSalon : id du salon
* @param idServeur : id du serveur
*/
int bdd_supprimer_salon(unsigned long int idSalon, unsigned long idServeur);

/**
* @brief supprime tous les salons d'un serveur
* @param idServeur : id du serveur
*/
int supprimer_salons_serveur(unsigned long int idServeur);

/**
* @brief renvoie l'id d'un salon
* @param id_serveur : id du serveur
* @param name : nom du salon
* @return revoie 0 si le salon n'existe pas sinon renvoie son id
*/
unsigned long int bdd_getSalon_id(unsigned long int id_serveur, const char * name);

/**
* @brief renvoie l'id d'un serveur
* @param id_salon : id du salon
*/
unsigned long int bdd_getServeur_id_by_salon_id(unsigned long int id_salon);

#endif
