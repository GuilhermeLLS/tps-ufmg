#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include "../include/Graph.hpp"

std::tuple<int, int> getVerticesAndNodes()
{
    std::string auxNodes, auxVertices;
    std::cin >> auxNodes >> auxVertices;
    return std::make_tuple(stoi(auxNodes), stoi(auxVertices));
}

int main()
{
    std::string auxFrom, auxTo;
    int numberOfNodes, numberOfVertices;
    std::tie(numberOfNodes, numberOfVertices) = getVerticesAndNodes();

    Graph *airportsGraph = new Graph(numberOfNodes);

    int counter = 0;
    while (counter < numberOfVertices)
    {
        std::cin >> auxFrom >> auxTo;
        airportsGraph->addPair(stoi(auxFrom) - 1, stoi(auxTo) - 1);
        counter++;
    }
    airportsGraph->findSSCsAndGetDegrees();
    airportsGraph->minimalAddition();
    return 0;
}
