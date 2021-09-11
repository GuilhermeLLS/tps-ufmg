#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <stack>
#include <list>
#include <vector>
#include <algorithm>

class Graph
{
private:
    int numberOfAirports;
    std::vector<std::vector<int>> scc;
    std::list<int> *airports;
    std::vector<int> grausIn;
    std::vector<int> grausOut;
    Graph *transpose();
    void dfsStack(int v, bool visited[], std::stack<int> &vertexStack);
    void dfsSsc(int v, bool visited[], int indexator, std::vector<std::vector<int>> &scc);
    void checkOuterDegrees(int elem);
    void initializeVisited(bool visited[]);
    void innerOutterDegrees();
    void initializeStorages();

public:
    Graph(int numberOfAirports);
    void addPair(int from, int to);
    void findSSCsAndGetDegrees();
    void minimalAddition();
};

#endif