#include "../headers/Serial.h"


unsigned long int incrementeSerial(char nomTable[]) {
	FILE *fichier = fopen("rsc/serial.dat", "r+");
	Serial serial;
	
	while((fread(&serial, sizeof(Serial), 1, fichier)) != EOF) {
		if (strcmp(serial.table_name, nomTable)) {
			fseek(fichier, -sizeof(unsigned long int), SEEK_CUR);
			unsigned long int valSerialFinale = serial.count + 1;
			fwrite(&valSerialFinale, sizeof(unsigned long int), 1, fichier);
			return serial.count;
		}
	}
	return 0; //Table introuvale
}
