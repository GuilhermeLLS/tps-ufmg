#include <stdlib.h>
#include <arpa/inet.h>

struct switchRack
{
    int id;
    int message;
    struct switchRack *prev, *next;
};

struct rack
{
    int id;
    int size;
    int MAX_SIZE;
    struct switchRack *first, *last;
};

struct dataCenter
{
    struct rack *racks;
    int size;
    int MAX_SIZE;
};

void initDataCenter(struct dataCenter *dataCenter);
void getSwitchMessage(int id);
void addSwitchesToRack(struct dataCenter *dataCenter, char *switchesIds, char *rackId, char *response);
int checkAddSwitchToRack(struct dataCenter *dataCenter, int switchId, int rackId, char *response);
void addSwitchToRack(struct dataCenter *dataCenter, int switchId, int rackId);
int checkListSwitchesFromRack(struct dataCenter *dataCenter, int rackId, char *response);
void listSwitchesFromRack(struct dataCenter *dataCenter, int rackId, char *response);
int checkGetSwitchesData(struct dataCenter *dataCenter, char *switchesIds, char *rackId, char *response);
void getSwitchesData(struct dataCenter *dataCenter, char *switchesIds, char *rackId, char *response);
int checkRemoveSwitchFromRack(struct dataCenter *dataCenter, char *switchId, char *rackId, char *response);
void removeSwitchFromRack(struct dataCenter *dataCenter, char *switchId, char *rackId, char *response);
int getRandomNumber();
int hasNewLiner(char *value);
void addrtostr(const struct sockaddr *addr, char *str, size_t strsize);
int server_sockaddr_init(const char *proto, const char *portstr, struct sockaddr_storage *storage);
int addrparse(const char *addrstr, const char *portstr, struct sockaddr_storage *storage);