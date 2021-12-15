bin/prog: obj/main.o obj/membre.o obj/table.o obj/message.o obj/invitation.o obj/utilisateur.o obj/serial.o obj/connexions_action.o obj/acceuil_actions.o
	gcc obj/*.o -o bin/prog


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