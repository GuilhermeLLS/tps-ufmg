#pragma once
#include <stdlib.h>
#include <arpa/inet.h>

void printErrorAndTerminate(char *message);

int addrparse(const char *addrstr, const char *portstr, struct sockaddr_storage *storage);

void addrtostr(const struct sockaddr *addr, char *str, size_t strsize);

int server_sockaddr_init(const char *portstr, struct sockaddr_storage *storage);

int checkCommand(char *input, char *command, char *delimiter);

int charToInt(char value);

void sendMessageAndCheckForErrors(int sock, char *message, int offset);