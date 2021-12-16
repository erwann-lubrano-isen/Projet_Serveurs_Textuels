#include "../headers/Invitation.h"

int bdd_creer_invitation(unsigned long int user_id, unsigned long int server_id){
	FILE * file = NULL;
	file = fopen("rsc/invitation.dat","r+");
	Invitation invitation;
	invitation.user_id=user_id;
	invitation.server_id=server_id;
	fseek(file, sizeof(Invitation)*(bdd_getSize_table("invitation")), SEEK_SET);
	fwrite(&invitation,sizeof(Invitation),1,file);
	fclose(file);
	file = NULL;
	bdd_increment_table("invitation");
}

void bdd_afficher_invitation(){
	int size = bdd_getSize_table("invitation");
	int i =0;
	Invitation invitation;
	FILE * file = NULL;
	file = fopen("rsc/invitation.dat","r");
	while(fread(&invitation,sizeof(Invitation),1,file) != EOF && i < size){
		printf("user : %lu\t serveur: %lu\n",invitation.user_id,invitation.server_id);
		++i;
	}
	fclose(file);
}

int bdd_supprimer_invitation(unsigned long int user_id, unsigned long int server_id){
	int size = bdd_getSize_table("invitation");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("invitation");
		return 0;
	}
	int i =0;
	Invitation invitation;
	Invitation derniereInvitation;
	FILE * file = NULL;
	file = fopen("rsc/invitation.dat","r+");
	fseek(file,sizeof(Invitation)*(size-1),SEEK_SET);
	fread(&derniereInvitation,sizeof(Invitation),1,file);
	fseek(file,0,SEEK_SET);
	while(fread(&invitation,sizeof(Invitation),1,file) != EOF && i < size){
		++i;
		if(invitation.user_id==user_id && invitation.server_id == server_id){
			fseek(file,-sizeof(Invitation),SEEK_CUR);
			fwrite(&derniereInvitation,sizeof(Invitation),1,file);
			if(size>=1){
				bdd_decrement_table("invitation");
				--size;
			}
			--i;
			fseek(file,sizeof(Invitation)*(size-1),SEEK_SET);
			fread(&derniereInvitation,sizeof(Invitation),1,file);
			fseek(file,i*(sizeof(Invitation)),SEEK_SET);
		}
	}
	fclose(file);
	return 0;
}
int bdd_supprimer_invitation_parId(unsigned long int user_id){
	int size = bdd_getSize_table("invitation");
	if(size==0)return 0;
	if(size==1){
		bdd_decrement_table("invitation");
		return 0;
	}
	int i =0;
	Invitation invitation;
	Invitation derniereInvitation;
	FILE * file = NULL;
	file = fopen("rsc/invitation.dat","r+");
	fseek(file,sizeof(Invitation)*(size-1),SEEK_SET);
	fread(&derniereInvitation,sizeof(Invitation),1,file);
	fseek(file,0,SEEK_SET);
	while(fread(&invitation,sizeof(Invitation),1,file) != EOF && i < size){
		++i;
		if(invitation.user_id==user_id){
			fseek(file,-sizeof(Invitation),SEEK_CUR);
			fwrite(&derniereInvitation,sizeof(Invitation),1,file);
			if(size>=1){
				bdd_decrement_table("invitation");
				--size;
			}
			--i;
			fseek(file,sizeof(Invitation)*(size-1),SEEK_SET);
			fread(&derniereInvitation,sizeof(Invitation),1,file);
			fseek(file,i*(sizeof(Invitation)),SEEK_SET);
		}
	}
	fclose(file);
	return 0;
}
