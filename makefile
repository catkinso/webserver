webserver: webserver.c
	gcc -o webserver webserver.c

all: webserver

clean:
	rm webserver
