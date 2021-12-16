bin/prog: obj/main.o obj/membre.o obj/table.o obj/message.o obj/invitation.o obj/utilisateur.o obj/serial.o obj/serveur.o obj/salon.o obj/menusalon.o  obj/permissions_salon.o obj/connexions_action.o obj/acceuil_actions.o obj/demande.o obj/permissions_serveur.o obj/serveurmenu.o 
	gcc obj/*.o -o bin/prog


obj/permissions_salon.o: src/Permissions_Salon.c headers/Permissions_Salon.h
	gcc -o obj/permissions_salon.o -c src/Permissions_Salon.c

obj/menusalon.o: src/MenuSalon.c headers/MenuSalon.h
	gcc -o obj/menusalon.o -c src/MenuSalon.c

obj/serveur.o: src/Serveur.c headers/Serveur.h headers/Membre.h headers/Table.h
	gcc -o obj/serveur.o -c src/Serveur.c

obj/salon.o: src/salon.c headers/Salon.h 
	gcc -o obj/salon.o -c src/salon.c

obj/membre.o: src/Membre.c headers/Membre.h headers/Table.h
	gcc -o obj/membre.o -c src/Membre.c

obj/serial.o: src/Serial.c headers/Serial.h
	gcc -o obj/serial.o -c src/Serial.c

obj/main.o: main.c
	gcc  -o obj/main.o -c main.c

obj/table.o: src/Table.c headers/Table.h
	gcc -o obj/table.o -c src/Table.c

obj/message.o: src/Message.c headers/Message.h
	gcc -o obj/message.o -c src/Message.c

obj/invitation.o: src/Invitation.c headers/Invitation.h
	gcc -o obj/invitation.o -c src/Invitation.c

obj/utilisateur.o: src/Utilisateur.c headers/Utilisateur.h headers/Serial.h headers/Table.h
	gcc -o obj/utilisateur.o -c src/Utilisateur.c

obj/connexions_action.o: headers/Connexions_Action.h src/Connexions_Action.c headers/Utilisateur.h headers/Table.h headers/Connexions_Action.h 
	gcc -o obj/connexions_action.o -c src/Connexions_Action.c
	
obj/acceuil_actions.o: headers/Acceuil_Actions.h src/Acceuil_Actions.c
	gcc -o obj/acceuil_actions.o -c src/Acceuil_Actions.c

obj/demande.o: src/Demande.c headers/Demande.h headers/Table.h 
	gcc -c src/Demande.c -o obj/demande.o
	
obj/permissions_serveur.o: src/Permissions_Serveur.c headers/Permissions_Serveur.h headers/Table.h
	gcc -c src/Permissions_Serveur.c -o obj/permissions_serveur.o

obj/serveurmenu.o: src/ServeurMenu.c headers/ServeurMenu.h
	gcc -c src/ServeurMenu.c -o obj/serveurmenu.o
