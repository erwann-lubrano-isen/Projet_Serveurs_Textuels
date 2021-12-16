#include "../headers/Serial.h"


unsigned long int incrementeSerial(char nomTable[]) {	//Permet d'incrementer le sérial de la table correspondante
	FILE *fichier = fopen("rsc/serial.dat", "r+");
	Serial serial;
	
	while((fread(&serial, sizeof(Serial), 1, fichier)) != EOF) {
		if (strcmp(serial.table_name, nomTable)) {
			fseek(fichier, -sizeof(unsigned long int), SEEK_CUR);
			unsigned long int valSerialFinale = serial.count + 1;
			fwrite(&valSerialFinale, sizeof(unsigned long int), 1, fichier);
			fclose(fichier);
			return serial.count;
		}
	}
	fclose(fichier);
	return -1; //Table introuvale
}
