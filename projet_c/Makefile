test.exe: main.o
	gcc main.o -o main.exe `pkg-config opencv --libs` 
test.o: main.c
	gcc -Wall main.c -c `pkg-config opencv --cflags` 
clean:
	rm -rf *~
	rm -rf *.o
	rm -rf *.exe
