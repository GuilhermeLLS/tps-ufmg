#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "../include/Graph.hpp"

int main(int argc, char *argv[])
{
    std::string taskType = argv[1];
    std::string fileName = argv[2];
    int auxFrom, auxTo, trailNumber, verticesNumber;
    std::ifstream dataInput(fileName);

    dataInput >> verticesNumber >> trailNumber;
    Graph *g = new Graph(verticesNumber);

    int counter = 0;
    while (counter < trailNumber)
    {
        dataInput >> auxFrom >> auxTo;
        g->addPair(auxFrom, auxTo);
        counter++;
    }

    dataInput.close();

    std::ofstream dataOutput("result.txt");

    if (taskType == "tarefa1")
    {
        dataOutput << g->findMinimalWarehouseAddition();
    }
    if (taskType == "tarefa2")
    {
        clock_t time = clock();
        int amountOfWarehouses;
        bool *warehouses;
        std::tie(amountOfWarehouses, warehouses) = g->findApproximateMinimalWarehouseAddition();
        dataOutput << amountOfWarehouses << std::endl;
        for (int i = 0; i < verticesNumber; i++)
        {
            if (warehouses[i])
            {
                dataOutput << i << std::endl;
            }
        }
        time = clock() - time;
        std::cout << "Time: " << time << std::endl;
    }

    dataOutput.close();

    return 0;
}
