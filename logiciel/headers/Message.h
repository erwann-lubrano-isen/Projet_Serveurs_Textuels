#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include <stdio.h>
#include <time.h>
#include <string.h>

#include "Table.h"


/**
* @struct Message
* @brief messages envoyés sur un salon
*/
typedef struct Message{
	unsigned long int id_salon;
	unsigned long int id_utilisateur;
	time_t date;
	char texte[120];
}Message;

/**
* @brief permet de creer un message
* @param id_salon : id du salon ou écrire le message
* @param id_utilisateur : id de l'utilisateur qui a écrit le message
* @param date : moment ou le message a été écrit
* @param texte : contenu du message
*/
int bdd_creer_message(unsigned long int id_salon, unsigned long int id_utilisateur, time_t date, const char * const texte);

/**
* @brief affiche tous les messages
*/
void bdd_afficherMessages();

/**
* @brief supprime un message
* @param id_salon : id du salon le message a été écrit
* @param id_utilisateur : id de l'utilisateur qui a écrit le message
* @param date : moment ou le message a été écrit
*/
int bdd_supprimer_message(unsigned long int id_salon, unsigned long int id_utilisateur, time_t date);
	
#endif
