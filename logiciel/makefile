bin/prog: obj/main.o obj/membre.o obj/table.o obj/message.o obj/invitation.o obj/utilisateur.o obj/serial.o
	gcc obj/*.o -o bin/prog


obj/membre.o: src/Membre.c headers/Membre.h headers/Table.h
	gcc -o obj/membre.o -c src/Membre.c

obj/serial.o: src/Serial.c headers/Serial.h
	gcc -o obj/serial.o -c src/Serial.c

obj/main.o: main.c
	gcc  -o obj/main.o -c main.c

obj/table.o: src/Table.c headers/Table.h
	gcc -o obj/table.o -c src/Mable.c

obj/message.o: src/Message.c headers/Message.h
	gcc -o obj/message.o -c src/Message.c

obj/invitation.o: src/Invitation.c headers/Invitation.h
	gcc -o obj/invitation.o -c src/Invitation.c

obj/utilisateur.o: src/Utilisateur.c headers/Utilisateur.h headers/Serial.h headers/Table.h
	gcc -o obj/utilisateur.o -c src/Utilisateur.c
