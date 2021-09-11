#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <list>
#include <tuple>

class Graph
{
private:
    int amountOfVillages;
    std::list<int> *villages;
    void dfs(int v, bool visited[], bool selectedVertices[]);
    void initializeBool(bool arr[]);
    int getAmountOfSelectedVertices(bool selectedVertices[]);

public:
    Graph(int amountOfVillages);
    void addPair(int from, int to);
    int findMinimalWarehouseAddition();
    std::tuple<int, bool*>findApproximateMinimalWarehouseAddition();
};

#endif
