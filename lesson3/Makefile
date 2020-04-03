
all: main.o
	gcc -g main.o -o main.out

main.o: main.c
	gcc -Wall $(DEFINE) -c main.c -o main.o

clean:
	-$(RM) *.o
