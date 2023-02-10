#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include "common.h"

void initDataCenter(struct dataCenter *dataCenter)
{
    dataCenter->size = 0;
    dataCenter->MAX_SIZE = 4;
    dataCenter->racks = malloc(4 * sizeof(struct rack));
}

void addSwitchesToRack(struct dataCenter *dataCenter, char *switchesIds, char *rackId, char *response)
{
    char *copiedSwIds = strdup(switchesIds);
    int parsedRackId = atoi(rackId);
    char *aux = strtok(copiedSwIds, " ");
    int parsedSwitch, hasProblem = 0, amountOfSws = 0;
    while (aux != NULL)
    {
        parsedSwitch = atoi(aux);
        if (checkAddSwitchToRack(dataCenter, parsedSwitch, parsedRackId, response) == 0)
        {
            hasProblem = 1;
            break;
        }
        aux = strtok(NULL, " ");
        amountOfSws++;
    }
    if (amountOfSws >= 4 && hasProblem == 0)
    {
        hasProblem = 1;
        strcpy(response, "error rack limit exceeded\n");
    }
    if (hasProblem == 0)
    {
        char *copyForMessage = strdup(switchesIds);
        char *ptr = strtok(switchesIds, " ");
        while (ptr != NULL)
        {
            parsedSwitch = atoi(ptr);
            ptr = strtok(NULL, " ");
            addSwitchToRack(dataCenter, parsedSwitch, parsedRackId);
        }
        snprintf(response, 500, "switch%sinstalled", copyForMessage);
    }
}

int checkAddSwitchToRack(struct dataCenter *dataCenter, int switchId, int rackId, char *response)
{
    if (switchId < 1 || switchId > 4)
    {
        strcpy(response, "error switch type unknown\n");
        return 0;
    }

    struct rack pickedRack = dataCenter->racks[rackId - 1];
    if (pickedRack.size + 1 > 3)
    {
        strcpy(response, "error rack limit exceeded\n");
        return 0;
    }

    struct switchRack *auxSw = pickedRack.first;
    if (auxSw != NULL)
    {
        for (size_t j = 0; j < pickedRack.size; j++)
        {
            if (auxSw->id == switchId)
            {
                snprintf(response, 500, "error switch 0%d already installed in 0%d", switchId, rackId);
                return 0;
            }
            auxSw = auxSw->next;
        }
    }
    return 1;
}

int checkListSwitchesFromRack(struct dataCenter *dataCenter, int rackId, char *response)
{
    if (rackId < 1 || rackId > 4)
    {
        strcpy(response, "error rack doesn't exist");
        return 0;
    }
    if (dataCenter->racks[rackId - 1].size == 0)
    {
        strcpy(response, "empty rack");
        return 0;
    }

    return 1;
}

void listSwitchesFromRack(struct dataCenter *dataCenter, int rackId, char *response)
{
    char aux[50];
    if (checkListSwitchesFromRack(dataCenter, rackId, response) == 1)
    {
        struct switchRack *auxSw = dataCenter->racks[rackId - 1].first;
        if (auxSw != NULL)
        {
            for (size_t j = 0; j < dataCenter->racks[rackId - 1].size; j++)
            {
                snprintf(aux, 50, "0%d ", auxSw->id);
                strcat(response, aux);
                auxSw = auxSw->next;
            }
        }
    }
}

void getSwitchesData(struct dataCenter *dataCenter, char *switchesIds, char *rackId, char *response)
{
    char aux[50];
    if (checkGetSwitchesData(dataCenter, strdup(switchesIds), rackId, response))
    {
        int parsedSwitch;
        int parsedRackId = atoi(rackId);
        char *ptr = strtok(switchesIds, " ");
        while (ptr != NULL)
        {
            parsedSwitch = atoi(ptr);
            struct switchRack *auxSw = dataCenter->racks[parsedRackId - 1].first;
            if (auxSw != NULL)
            {
                for (size_t j = 0; j < dataCenter->racks[parsedRackId - 1].size; j++)
                {
                    if (auxSw->id == parsedSwitch)
                    {
                        snprintf(aux, 50, "%d Kbs ", auxSw->message);
                        strcat(response, aux);
                    }
                    auxSw = auxSw->next;
                }
            }
            ptr = strtok(NULL, " ");
        }
    }
}

int hasElement(struct switchRack *auxSw, int size, int element)
{
    for (size_t j = 0; j < size; j++)
    {
        if (auxSw->id == element)
        {
            return 1;
        }
        auxSw = auxSw->next;
    }
    return 0;
}

int checkGetSwitchesData(struct dataCenter *dataCenter, char *switchesIds, char *rackId, char *response)
{
    int parsedSwitch;
    int parsedRackId = atoi(rackId);
    char *ptr = strtok(switchesIds, " ");

    while (ptr != NULL)
    {
        parsedSwitch = atoi(ptr);
        struct switchRack *auxSw = dataCenter->racks[parsedRackId - 1].first;
        if (auxSw != NULL)
        {
            if (!hasElement(auxSw, dataCenter->racks[parsedRackId - 1].size, parsedSwitch))
            {
                strcpy(response, "error switch doesn't exist");
                return 0;
            }
        }
        else
        {
            strcpy(response, "error rack doesn't exist");
            return 0;
        }
        ptr = strtok(NULL, " ");
    }

    return 1;
}

int checkRemoveSwitchFromRack(struct dataCenter *dataCenter, char *switchId, char *rackId, char *response)
{
    int parsedSwId = atoi(switchId);
    int parsedRackId = atoi(rackId);
    if (parsedSwId < 1 || parsedSwId > 4)
    {
        strcpy(response, "error switch type unknown\n");
        return 0;
    }

    struct switchRack *auxSw = dataCenter->racks[parsedRackId - 1].first;
    if (!hasElement(auxSw, dataCenter->racks[parsedRackId - 1].size, parsedSwId))
    {
        strcpy(response, "error switch doesn't exist");
        return 0;
    }

    return 1;
}

void removeSwitchFromRack(struct dataCenter *dataCenter, char *switchId, char *rackId, char *response)
{
    if (checkRemoveSwitchFromRack(dataCenter, switchId, rackId, response))
    {
        int parsedSwId = atoi(switchId);
        int parsedRackId = atoi(rackId);
        struct rack pickedRack = dataCenter->racks[parsedRackId - 1];
        struct switchRack *auxSw = pickedRack.first;

        for (size_t j = 0; j < pickedRack.size; j++)
        {
            if (auxSw->id == parsedSwId)
            {
                if (j == 0)
                {
                    if (pickedRack.size > 1)
                    {
                        pickedRack.first->next->prev = NULL;
                        pickedRack.first = pickedRack.first->next;
                    }
                    else
                    {
                        pickedRack.first = NULL;
                        pickedRack.last = NULL;
                    }
                    break;
                }
                else if (j == pickedRack.size - 1)
                {
                    pickedRack.last = pickedRack.last->prev;
                    pickedRack.last->next->prev = NULL;
                    pickedRack.last->next = NULL;
                    break;
                }
                else
                {
                    auxSw->prev->next = auxSw->next;
                    auxSw->next->prev = auxSw->prev;
                    break;
                }
            }
            auxSw = auxSw->next;
        }
        pickedRack.size--;
        dataCenter->racks[parsedRackId - 1] = pickedRack;
        snprintf(response, 500, "switch%sremoved from %s", switchId, rackId);
    }
}

int getRandomNumber()
{
    return (rand() % 7000) + 1;
}

void addSwitchToRack(struct dataCenter *dataCenter, int switchId, int rackId)
{
    struct rack pickedRack;
    int found = 0;
    for (size_t i = 0; i < 4; i++)
    {
        if (dataCenter->racks[i].id == rackId)
        {
            found = 1;
            pickedRack = dataCenter->racks[i];
            break;
        }
    }
    if (found == 0)
    {
        pickedRack.id = rackId;
        pickedRack.size = 0;
        pickedRack.first = NULL;
        pickedRack.last = NULL;
    }

    pickedRack.size++;
    dataCenter->size++;
    struct switchRack *sw = malloc(sizeof(struct switchRack));
    sw->id = switchId;
    sw->message = getRandomNumber();
    sw->prev = NULL;
    sw->next = NULL;
    if (pickedRack.first == NULL && pickedRack.last == NULL)
    {
        pickedRack.first = sw;
        pickedRack.last = sw;
    }
    else
    {
        sw->prev = pickedRack.last;
        sw->prev->next = sw;
        pickedRack.last = sw;
    }
    dataCenter->racks[rackId - 1] = pickedRack;
}

int addrparse(const char *addrstr, const char *portstr,
              struct sockaddr_storage *storage)
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
    port = htons(port);

    struct in_addr inaddr4;
    if (inet_pton(AF_INET, addrstr, &inaddr4))
    {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
        addr4->sin_family = AF_INET;
        addr4->sin_port = port;
        addr4->sin_addr = inaddr4;
        return 0;
    }

    struct in6_addr inaddr6;
    if (inet_pton(AF_INET6, addrstr, &inaddr6))
    {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
        addr6->sin6_family = AF_INET6;
        addr6->sin6_port = port;
        memcpy(&(addr6->sin6_addr), &inaddr6, sizeof(inaddr6));
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
        inet_ntop(AF_INET, &(addr4->sin_addr), addrstr, INET6_ADDRSTRLEN + 1);
        port = ntohs(addr4->sin_port);
    }
    else if (addr->sa_family == AF_INET6)
    {
        version = 6;
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)addr;
        inet_ntop(AF_INET6, &(addr6->sin6_addr), addrstr, INET6_ADDRSTRLEN + 1);
        port = ntohs(addr6->sin6_port);
    }
    if (str)
    {
        snprintf(str, strsize, "IPv%d %s %hu", version, addrstr, port);
    }
}

int hasNewLiner(char *value)
{
    for (size_t i = 0; i < strlen(value); i++)
    {
        // 10 = new liner character
        if (value[i] == 10)
        {
            return 1;
        }
    }

    return 0;
}

int server_sockaddr_init(const char *proto, const char *portstr,
                         struct sockaddr_storage *storage)
{
    uint16_t port = (uint16_t)atoi(portstr);
    if (port == 0)
    {
        return -1;
    }
    port = htons(port);

    memset(storage, 0, sizeof(*storage));
    if (0 == strcmp(proto, "v4"))
    {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)storage;
        addr4->sin_family = AF_INET;
        addr4->sin_addr.s_addr = INADDR_ANY;
        addr4->sin_port = port;
        return 0;
    }
    else if (0 == strcmp(proto, "v6"))
    {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)storage;
        addr6->sin6_family = AF_INET6;
        addr6->sin6_addr = in6addr_any;
        addr6->sin6_port = port;
        return 0;
    }
    else
    {
        return -1;
    }
}