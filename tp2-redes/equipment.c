#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024
#define INVALID -1
#define SENDER_ID_POSITION 9
#define RECIPIENT_ID_POSITION 13

pthread_t tid_send;
pthread_t tid_recv;

int selfId;
int ALLOW_CONNEXION_SEND = 1;
int ALLOW_CONNEXION_RECEIVEMENT = 1;

struct DataFromClient
{
    int s;
};

void usage(int argc, char **argv)
{
    printf("usage: %s <server IP> <server port>\n", argv[0]);
    printf("exemple: %s 127.0.0.1 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

void sendConnectionTermination(int socket)
{
    char message[BUFSZ];
    snprintf(message, 1024, "REQ_RM(0%d)\n", selfId);
    sendMessageAndCheckForErrors(socket, message, 0);
}

void sendRequestInfo(char *message, int socket)
{
    int recipientId = charToInt(message[26]);
    char aux[BUFSZ];
    snprintf(aux, 1024, "REQ_INF(0%d, 0%d)\n", selfId, recipientId);
    sendMessageAndCheckForErrors(socket, aux, 0);
}

void sendRequestList(int socket)
{
    char message[BUFSZ];
    snprintf(message, 1024, "REQ_LIST(0%d)\n", selfId);
    sendMessageAndCheckForErrors(socket, message, 0);
}

void *sendingThread(void *data)
{
    struct DataFromClient *cdata = (struct DataFromClient *)data;
    while (ALLOW_CONNEXION_SEND)
    {
        char response[BUFSZ];
        char auxResponse[BUFSZ];
        memset(response, 0, BUFSZ);
        memset(auxResponse, 0, BUFSZ);
        scanf("%[^\n]%*c", response);
        memcpy(auxResponse, response, strlen(response) + 1);

        if (checkCommand(auxResponse, "request information from ", "0") == 0)
        {
            sendRequestInfo(response, cdata->s);
        }
        else if (checkCommand(auxResponse, "close connection", "0") == 0)
        {
            sendConnectionTermination(cdata->s);
            ALLOW_CONNEXION_SEND = 0;
        }
        else if (checkCommand(auxResponse, "list equipment", "0") == 0)
        {
            sendRequestList(cdata->s);
        }
    }

    pthread_exit(EXIT_SUCCESS);
}

void handleReceiveAddResponse(char *message)
{
    int recipientId = charToInt(message[9]);
    if (selfId == INVALID)
    {
        selfId = recipientId;
        printf("New ID: 0%d\n", selfId);
    }
    else
    {
        printf("Equipment 0%d added\n", recipientId);
    }
}

void handleReceiveListResponse(char *message)
{
    char auxMessage[BUFSZ];
    strcpy(auxMessage, message);
    char *equipments = strtok(auxMessage + strlen(strtok(auxMessage, "(")) + 1, ")");
    printf("%s\n", equipments);
}

void handleRequestRemove(char *message)
{
    printf("Equipment 0%d removed\n", charToInt(message[8]));
}

void handleRequestInformation(char *message, int sock)
{
    printf("requested information\n");
    int senderId = charToInt(message[SENDER_ID_POSITION]);
    int recipientId = charToInt(message[RECIPIENT_ID_POSITION]);
    float randomNumber = ((float)rand() / (float)(RAND_MAX)) * 10;
    char mensagem[BUFSZ] = "";
    snprintf(mensagem, 1024, "RES_INF(0%d, 0%d, %.2f)\n", senderId, recipientId, randomNumber);
    sendMessageAndCheckForErrors(sock, mensagem, 0);
}

void handleReceiveInformationResponse(char *message, int sock)
{
    char auxMessage[BUFSZ];
    int recipientId = charToInt(message[RECIPIENT_ID_POSITION]);
    strcpy(auxMessage, message);
    char *value = strtok(auxMessage + 16, ")");
    printf("Value from 0%d: %s\n", recipientId, value);
}

int handleRequestReceivement(char *auxResponse, char *response, int socket)
{
    if (checkCommand(auxResponse, "REQ_RM", "(") == 0)
    {
        handleRequestRemove(response);
        return 1;
    }
    else if (checkCommand(auxResponse, "REQ_INF", "(") == 0)
    {
        handleRequestInformation(response, socket);
        return 1;
    }
    return 0;
}

int handleResponseReceivement(char *auxResponse, char *response, int socket)
{
    if (checkCommand(auxResponse, "RES_ADD", "(") == 0)
    {
        handleReceiveAddResponse(response);
        return 1;
    }
    else if (checkCommand(auxResponse, "RES_LIST", "(") == 0)
    {
        handleReceiveListResponse(response);
        return 1;
    }
    else if (checkCommand(auxResponse, "RES_INF", "(") == 0)
    {
        handleReceiveInformationResponse(response, socket);
        return 1;
    }
    return 0;
}

int handleErrorReceivement(char *response)
{
    if (strcmp(response, "ERROR(01)\n") == 0)
    {
        printf("Equipment not found\n");
        return 1;
    }
    else if (strcmp(response, "ERROR(02)\n") == 0)
    {
        printf("Source equipment not found\n");
        return 1;
    }
    else if (strcmp(response, "ERROR(03)\n") == 0)
    {
        printf("Target equipment not found\n");
        return 1;
    }
    else if (strcmp(response, "ERROR(04)\n") == 0)
    {
        printf("Equipment limit exceeded\n");
        ALLOW_CONNEXION_RECEIVEMENT = 0;
        return 1;
    }
    return 0;
}

void *receivementThread(void *data)
{
    struct DataFromClient *cdata = (struct DataFromClient *)data;
    while (ALLOW_CONNEXION_RECEIVEMENT)
    {
        char response[BUFSZ];
        char auxResponse[BUFSZ];
        memset(response, 0, BUFSZ);
        memset(auxResponse, 0, BUFSZ);
        recv(cdata->s, response, BUFSZ, 0);
        strcpy(auxResponse, response);

        if (strcmp(response, "OK(01)\n") == 0)
        {
            printf("Success\n");
            ALLOW_CONNEXION_RECEIVEMENT = 0;
        }
        else if (handleRequestReceivement(auxResponse, response, cdata->s) == 0)
        {
            if (handleResponseReceivement(auxResponse, response, cdata->s) == 0)
            {

                handleErrorReceivement(response);
            }
        }
    }
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != addrparse(argv[1], argv[2], &storage))
    {
        usage(argc, argv);
    }

    int sSocket;
    sSocket = socket(storage.ss_family, SOCK_STREAM, 0);
    srand(time(NULL)); // Initialization, should only be called once.

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    connect(sSocket, addr, sizeof(storage));

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);

    fflush(stdin);

    struct DataFromClient *cdata = malloc(sizeof(*cdata));
    selfId = INVALID;
    cdata->s = sSocket;

    pthread_create(&tid_send, NULL, sendingThread, cdata);
    pthread_create(&tid_recv, NULL, receivementThread, cdata);

    while (ALLOW_CONNEXION_RECEIVEMENT && ALLOW_CONNEXION_SEND)
    {
        continue;
    }
    close(sSocket);
    exit(EXIT_SUCCESS);
}
