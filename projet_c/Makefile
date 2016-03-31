interface.exe : interface.c
		gcc -o interface.exe  interface.c -Wall `pkg-config --cflags --libs gtk+-2.0`

main.exe : main.o traitement.o
		gcc main.o traitement.o -o main.exe `pkg-config opencv --libs`

main.o : main.c traitement.h
		gcc -o main.o -c main.c -Wall `pkg-config opencv --cflags`

traitement.o : traitement.c traitement.h
		gcc -o traitement.o -c traitement.c -Wall `pkg-config opencv --cflags`