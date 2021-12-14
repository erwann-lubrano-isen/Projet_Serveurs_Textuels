#include "headers/Serial.h"
#include "headers/Serveur.h"
#include "headers/Salon.h"
int main() {
	bd_creationServeur("LeServeur", 53);
	bd_create_Salon("salon 1",21);
	printf("%d\n",bd_Salon_check(1,21));
	return 0;
}
