#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "common.h"

void usage(int argc, char **argv)
{
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

#define BUFSZ 500

int main(int argc, char **argv)
{
	struct sockaddr_storage storage;
	addrparse(argv[1], argv[2], &storage);

	int sSocket;
	sSocket = socket(storage.ss_family, SOCK_STREAM, 0);

	struct sockaddr *addr = (struct sockaddr *)(&storage);
	connect(sSocket, addr, sizeof(storage));

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	char buf[BUFSZ];
	while (1)
	{
		memset(buf, 0, BUFSZ);
		fgets(buf, BUFSZ - 1, stdin);
		send(sSocket, buf, strlen(buf), 0);
		memset(buf, 0, BUFSZ);
		recv(sSocket, buf, BUFSZ, 0);
		puts(buf);
	}
	close(sSocket);
	exit(EXIT_SUCCESS);
}
