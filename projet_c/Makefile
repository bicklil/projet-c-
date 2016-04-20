main.exe : main.o traitement.o interface.o
		gcc main.o traitement.o interface.o -o main.exe `pkg-config opencv --libs gtk+-2.0`


main.o : main.c traitement.h
		gcc -o main.o -c main.c -Wall `pkg-config opencv --cflags gtk+-2.0`

traitement.o : traitement.c traitement.h
		gcc -o traitement.o -c traitement.c -Wall `pkg-config opencv --cflags`
		
interface.o : interface.c interface.h
		gcc -o interface.o -c interface.c -Wall `pkg-config --cflags gtk+-2.0`
		
clean:
	rm -rf *~
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.csv