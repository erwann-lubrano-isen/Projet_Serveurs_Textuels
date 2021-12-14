#include "../headers/Table.h"

int bdd_increment_table(const char * const name){
	FILE * file =NULL;
	file= fopen("rsc/table.dat","r+");
	if(file==NULL)return -1;
	Table table;
	while(fread(&table,sizeof(Table),1,file) != EOF){
		if(strcmp(table.name,name)==0){
			fseek(file,-sizeof(Table),SEEK_CUR);
			++table.size;
			printf("%s\t%d\n",table.name,table.size);
			fwrite(&table,sizeof(Table),1,file);
			break;
		}
	}
	fclose(file);
	return 0;
}

int bdd_getSize_table(const char * const name){
	FILE * file =NULL;
	file= fopen("rsc/table.dat","r");
	if(file==NULL)return -1;
	Table table;
	while(fread(&table,sizeof(Table),1,file) != EOF){
		if(strcmp(table.name,name)==0){
			fclose(file);
			return table.size;
		}
	}
	fclose(file);
	return -2;
}