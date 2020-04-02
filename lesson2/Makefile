all: exe

exe: solution.o
	gcc solution.o -ldl -Wl,-rpath,. -o  solution

solution.o: solution.c
	gcc -c solution.c -o solution.o

clean:
	-$(RM) *.o


