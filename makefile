webserver: webserver.o webfiles.o
	gcc -o webserver webserver.o webfiles.o

webserver.o: webserver.c webfiles.h
	gcc -c webserver.c

webfiles.o: webfiles.c webfiles.h
	gcc -c webfiles.c

all: webserver

clean:
	rm webserver *.o
