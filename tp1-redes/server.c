#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include "common.h"

#define BUFSZ 500

char *RACK_DELIMITER = "in";
char *SWITCH_DELIMITER = "sw";

int main(int argc, char **argv)
{
    struct dataCenter dataCenter;
    initDataCenter(&dataCenter);
    srand(time(NULL)); // Initialization, should only be called once.
    struct sockaddr_storage storage;
    server_sockaddr_init(argv[1], argv[2], &storage);

    int sSocket;
    sSocket = socket(storage.ss_family, SOCK_STREAM, 0);

    int enable = 1;
    setsockopt(sSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    bind(sSocket, addr, sizeof(storage));

    listen(sSocket, 10);
    while (1)
    {
        struct sockaddr_storage cstorage;
        struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
        socklen_t caddrlen = sizeof(cstorage);

        int csock = accept(sSocket, caddr, &caddrlen);

        char caddrstr[BUFSZ];
        addrtostr(caddr, caddrstr, BUFSZ);

        char receive[BUFSZ];
        char buf[BUFSZ];
        memset(buf, 0, BUFSZ);
        int messageFinished = 0;
        while (1)
        {
            memset(receive, 0, BUFSZ);
            recv(csock, receive, BUFSZ - 1, 0);

            if (hasNewLiner(receive))
            {
                messageFinished = 1;
            }
            if (messageFinished == 0)
            {
                strcpy(buf, receive);
                continue;
            }
            else
            {
                if (strlen(buf))
                {
                    char aux[BUFSZ] = "";
                    strcat(aux, buf);
                    strcat(aux, receive);
                    strcpy(receive, aux);

                    memset(buf, 0, BUFSZ);
                }
                messageFinished = 0;
            }

            char *message;
            char *end_external_str_tok_r;
            char response[BUFSZ] = "";

            if (strcmp(receive, "exit") == 0)
            {
                close(csock);
                exit(EXIT_SUCCESS);
            }
            message = strtok_r(receive, "\n", &end_external_str_tok_r);
            while (message != NULL)
            {
                strcpy(response, "");
                char *command, *switches, *rack;
                char *end_internal_strtok_r = message;
                command = strtok_r(message, " ", &end_internal_strtok_r);
                if (strcmp(command, "add") == 0)
                {
                    switches = strtok_r(NULL, RACK_DELIMITER, &end_internal_strtok_r) + strlen(SWITCH_DELIMITER);
                    rack = strtok_r(NULL, "", &end_internal_strtok_r) + strlen(RACK_DELIMITER);
                    addSwitchesToRack(&dataCenter, switches, rack, response);
                }
                else if (strcmp(command, "ls") == 0)
                {
                    rack = strtok_r(NULL, "", &end_internal_strtok_r);
                    listSwitchesFromRack(&dataCenter, atoi(rack), response);
                }
                else if (strcmp(command, "get") == 0)
                {
                    switches = strtok_r(NULL, RACK_DELIMITER, &end_internal_strtok_r);
                    rack = strtok_r(NULL, "", &end_internal_strtok_r) + strlen(RACK_DELIMITER);
                    getSwitchesData(&dataCenter, switches, rack, response);
                }
                else if (strcmp(command, "rm") == 0)
                {
                    switches = strtok_r(NULL, RACK_DELIMITER, &end_internal_strtok_r) + strlen(SWITCH_DELIMITER);
                    rack = strtok_r(NULL, "", &end_internal_strtok_r) + strlen(RACK_DELIMITER);
                    removeSwitchFromRack(&dataCenter, switches, rack, response);
                }
                else
                {
                    close(csock);
                    exit(EXIT_SUCCESS);
                }
                strcat(response, "\n");
                send(csock, response, strlen(response), 0);
                message = strtok_r(NULL, "\n", &end_external_str_tok_r);
            }
        }
    }
    exit(EXIT_SUCCESS);
}
