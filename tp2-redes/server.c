#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAX_EQUIPMENTS 10
#define BUFSZ 1024
#define INVALID -1
#define SENDER_ID_POSITION 9
#define RECIPIENT_ID_POSITION 13

struct Equipment
{
    int id;
    int socket;
};

struct DataFromClient
{
    int csock;
    struct sockaddr_storage storage;
};

int equipmentCounter = 0;
struct Equipment equipments[MAX_EQUIPMENTS];

void initEquipments()
{
    for (size_t i = 0; i < MAX_EQUIPMENTS; i++)
    {
        equipments[i].id = INVALID;
        equipments[i].socket = INVALID;
    }

    equipmentCounter = 0;
}

void usage(int argc, char **argv)
{
    printf("usage: %s <server port>\n", argv[0]);
    printf("exemple: %s 5151\n", argv[0]);
    exit(EXIT_FAILURE);
}

void broadcastToClients(char *message)
{
    for (size_t i = 0; i < MAX_EQUIPMENTS; i++)
    {
        if (equipments[i].socket != INVALID)
        {
            sendMessageAndCheckForErrors(equipments[i].socket, message, 1);
        }
    }
}

void handleServerRequestRemove(char *message, int socket, int *allowConnection)
{
    char aux[BUFSZ];
    int recipientId = charToInt(message[8]);
    if (equipments[recipientId].id == INVALID)
    {
        sprintf(aux, "ERROR(01)\n");
        sendMessageAndCheckForErrors(socket, aux, 1);
        return;
    }
    equipments[recipientId].id = INVALID;
    equipments[recipientId].socket = INVALID;
    equipmentCounter--;
    *allowConnection = 0;

    sprintf(aux, "OK(01)\n");
    sendMessageAndCheckForErrors(socket, aux, 1);
    printf("Equipment 0%d removed\n", recipientId);
    snprintf(aux, 1024, "REQ_RM(0%d)\n", recipientId);
    broadcastToClients(aux);
}

void handleServerRequestList(char *message, int socket)
{
    char aux[10] = "";
    char response[BUFSZ] = "RES_LIST(";
    int senderId = charToInt(message[10]);

    for (size_t i = 0; i < MAX_EQUIPMENTS; i++)
    {
        if (equipments[i].id != senderId && equipments[i].id != INVALID)
        {
            snprintf(aux, 4, "0%d ", equipments[i].id);
            strcat(response, aux);
        }
    }
    strcat(response, ")\n");
    sendMessageAndCheckForErrors(socket, response, 1);
}

void handleServerRequestInformation(char *message, int socket)
{
    char response[BUFSZ];
    int senderId = charToInt(message[SENDER_ID_POSITION]);
    int recipientId = charToInt(message[RECIPIENT_ID_POSITION]);

    if (equipments[senderId].id == INVALID || equipments[recipientId].id == INVALID)
    {
        int errorNum = equipments[recipientId].id == INVALID ? 3 : 2;
        sprintf(response, "ERROR(0%d)\n", errorNum);
        sendMessageAndCheckForErrors(socket, response, 1);
        return;
    }
    snprintf(response, 1024, "REQ_INF(0%d, 0%d)\n", senderId, recipientId);
    sendMessageAndCheckForErrors(equipments[recipientId].socket, response, 1);
    return;
}

void handleServerResponseInformation(char *message, int socket)
{
    int senderId = charToInt(message[SENDER_ID_POSITION]);
    int recipientId = charToInt(message[RECIPIENT_ID_POSITION]);

    if (equipments[senderId].id == INVALID || equipments[recipientId].id == INVALID)
    {
        char errorMessage[BUFSZ];
        int errorNum = equipments[senderId].id == INVALID ? 2 : 3;
        printf("Equipment 0%d not found\n", senderId);
        sprintf(errorMessage, "ERROR(0%d)\n", errorNum);
        sendMessageAndCheckForErrors(socket, errorMessage, 1);
        return;
    }
    sendMessageAndCheckForErrors(equipments[senderId].socket, message, 1);
    return;
}

int findFirstFreePosition()
{
    int id = INVALID;
    for (size_t i = 0; i < MAX_EQUIPMENTS; i++)
    {
        if (equipments[i].id == INVALID)
        {
            id = i;
            break;
        }
    }

    return id;
}

void *equipmentThread(void *data)
{
    // TYPECAST
    struct DataFromClient *clientData = (struct DataFromClient *)data;
    char message[BUFSZ], res[BUFSZ];
    int allowConnection = 1;

    if (equipmentCounter > MAX_EQUIPMENTS - 1)
    {
        sprintf(res, "ERROR(04)\n");
        sendMessageAndCheckForErrors(clientData->csock, res, 1);
        allowConnection = 0;
    }
    else
    {
        int allocatedPosition = findFirstFreePosition();
        equipments[allocatedPosition].id = allocatedPosition;
        equipments[allocatedPosition].socket = clientData->csock;
        equipmentCounter++;

        printf("Equipment 0%d added\n", allocatedPosition);
        snprintf(res, 1024, "RES_ADD(0%d)\n", allocatedPosition);
        broadcastToClients(res);
        usleep(50000);
    }

    while (allowConnection)
    {
        char auxMessage[BUFSZ];
        memset(message, 0, BUFSZ);
        memset(auxMessage, 0, BUFSZ);
        recv(clientData->csock, message, BUFSZ - 1, 0);
        memcpy(auxMessage, message, strlen(message) + 1);

        if (checkCommand(auxMessage, "RES_INF", "(") == 0)
        {
            handleServerResponseInformation(message, clientData->csock);
        }
        else if (checkCommand(auxMessage, "REQ_RM", "(") == 0)
        {
            handleServerRequestRemove(message, clientData->csock, &allowConnection);
        }
        else if (checkCommand(auxMessage, "REQ_LIST", "(") == 0)
        {
            handleServerRequestList(message, clientData->csock);
        }
        else if (checkCommand(auxMessage, "REQ_INF", "(") == 0)
        {
            handleServerRequestInformation(message, clientData->csock);
        }
    }

    close(clientData->csock);
    pthread_exit(EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], &storage))
    {
        printf(" aquiii");
        usage(argc, argv);
    }

    int sSocket;
    sSocket = socket(storage.ss_family, SOCK_STREAM, 0);

    int enable = 1;
    setsockopt(sSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    bind(sSocket, addr, sizeof(storage));

    listen(sSocket, MAX_EQUIPMENTS);

    char addrstr[BUFSZ];
    addrtostr(addr, addrstr, BUFSZ);
    printf("bound to %s, waiting connections\n", addrstr);

    initEquipments();

    while (1)
    {
        char msg[BUFSZ] = "";
        char res[BUFSZ] = "";

        memset(msg, 0, BUFSZ);
        memset(res, 0, BUFSZ);

        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        char caddrstr[BUFSZ];
        memset(caddrstr, 0, BUFSZ);

        int csock = accept(sSocket, caddr, &caddrlen);
        if (csock == INVALID)
        {
            printErrorAndTerminate("accept");
        }

        struct DataFromClient *clientData = malloc(sizeof(*clientData));
        clientData->csock = csock;
        memcpy(&(clientData->storage), &storage, sizeof(storage));
        pthread_t tid;
        pthread_create(&tid, NULL, equipmentThread, clientData);
    }
    exit(EXIT_SUCCESS);
}