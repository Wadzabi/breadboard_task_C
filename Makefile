output: main.o breadboard.o
	gcc main.o breadboard.o -o output

main.o: main.c
	gcc -c main.c

breadboard.o: breadboard.c breadboard.h
	gcc -c breadboard.c

clean:
	rm *.o output