#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <arpa/inet.h>

int checkCommand(char *input, char *command, char *delimiter)
{
    return strcmp(strtok(input, delimiter), command);
}

int charToInt(char value)
{
    return value - '0';
}

void printErrorAndTerminate(char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

void sendMessageAndCheckForErrors(int sock, char *message, int offset)
{
    if (send(sock, message, strlen(message) + offset, 0) != strlen(message) + offset)
    {
        printErrorAndTerminate("error sending message to server");
    }
}

int addrparse(const char *addrstr, const char *portstr, struct sockaddr_storage *storage)
{

    if (addrstr == NULL || portstr == NULL)
    {
        return -1;
    }

    uint16_t port = (uint16_t)atoi(portstr);

    if (port == 0)
    {
        return -1;
    }

    port = htons(port); // host to network (litle endian)

    struct in_addr inaddr4; // 32 bit IP Address
    if (inet_pton(AF_INET, addrstr, &inaddr4))
    {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
        addr4->sin_family = AF_INET;
        addr4->sin_port = port;
        addr4->sin_addr = inaddr4;
        return 0;
    }

    return -1;
}

void addrtostr(const struct sockaddr *addr, char *str, size_t strsize)
{
    int version;
    char addrstr[INET6_ADDRSTRLEN + 1] = "";
    uint16_t port;

    if (addr->sa_family == AF_INET)
    {
        version = 4;
        struct sockaddr_in *addr4 = (struct sockaddr_in *)addr;
        if (!inet_ntop(AF_INET, &(addr4->sin_addr), addrstr, INET6_ADDRSTRLEN + 1))
        {
            printErrorAndTerminate("ntop");
        }
        port = ntohs(addr4->sin_port); // Network to host short
    }
    else
    {
        printErrorAndTerminate("unknown protocol family");
    }

    if (str)
    {
        snprintf(str, strsize, "IPv%d %s %hu", version, addrstr, port);
    }
}

int server_sockaddr_init(const char *portstr, struct sockaddr_storage *storage)
{
    uint16_t port = (uint16_t)atoi(portstr);
    if (port == 0)
    {
        return -1;
    }
    port = htons(port);
    memset(storage, 0, sizeof(*storage));

    struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
    addr4->sin_family = AF_INET;
    addr4->sin_addr.s_addr = INADDR_ANY; // Qualquer add disponivel no computador
    addr4->sin_port = port;
    return 0;
}