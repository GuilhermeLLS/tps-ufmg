all:
	gcc -Wall -c common.c
	gcc -Wall -pthread server.c common.o -o server
	gcc -Wall -pthread equipment.c common.o -o equipment
