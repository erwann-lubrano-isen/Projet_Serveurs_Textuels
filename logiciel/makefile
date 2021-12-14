bin/prog: obj/main.o obj/membre.o obj/table.o obj/message.o
	gcc obj/*.o -o bin/prog


obj/membre.o: src/Membre.c headers/Membre.h headers/Table.h
	gcc -o obj/membre.o -c src/Membre.c

obj/main.o: main.c headers/Membre.h 
	gcc  -o obj/main.o -c main.c

obj/table.o: src/Table.c headers/Table.h
	gcc -c src/Table.c -o obj/table.o

obj/message.o: src/Message.c headers/Message.h
	gcc -c src/Message.c -o obj/message.o