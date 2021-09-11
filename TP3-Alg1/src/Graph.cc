#include "../include/Graph.hpp"

Graph::Graph(int amountOfVillages)
{
    this->amountOfVillages = amountOfVillages;
    villages = new std::list<int>[amountOfVillages];
}

void Graph::addPair(int from, int to)
{
    this->villages[from].push_back(to);
    this->villages[to].push_back(from);
}

void Graph::dfs(int v, bool visited[], bool vertices[])
{
    visited[v] = true;
    std::list<int>::iterator i;
    for (i = this->villages[v].begin(); i != this->villages[v].end(); ++i)
    {
        if (!visited[*i])
        {
            this->dfs(*i, visited, vertices);
            if (vertices[*i] == false)
            {
                vertices[v] = true;
            }
        }
    }
}

void Graph::initializeBool(bool arr[])
{
    for (int i = 0; i < this->amountOfVillages; ++i)
    {
        arr[i] = false;
    }
}

int Graph::getAmountOfSelectedVertices(bool selectedVertices[])
{
    int selected = 0;
    for (int i = 0; i < this->amountOfVillages; ++i)
    {
        if (selectedVertices[i] == true)
        {
            selected++;
        }
    }
    return selected;
}

int Graph::findMinimalWarehouseAddition()
{
    bool *selectedVertices = new bool[this->amountOfVillages];
    bool *visited = new bool[this->amountOfVillages];
    this->initializeBool(selectedVertices);
    this->initializeBool(visited);

    for (int i = 0; i < this->amountOfVillages; ++i)
    {
        if (visited[i] == false)
        {
            this->dfs(i, visited, selectedVertices);
        }
    }

    return getAmountOfSelectedVertices(selectedVertices);
}

std::tuple<int, bool*> Graph::findApproximateMinimalWarehouseAddition()
{
    bool *selectedVertices = new bool[this->amountOfVillages];
    bool *visited = new bool[this->amountOfVillages];
    this->initializeBool(selectedVertices);
    this->initializeBool(visited);

    int auxX, auxY;

    std::list<int>::iterator j, k;
    for (int i = 0; i < this->amountOfVillages; ++i)
    {
        for (j = this->villages[i].begin(); j != this->villages[i].end(); ++j)
        {
            if (!visited[i] && !visited[*j])
            {
                visited[i] = true;
                visited[*j] = true;
                selectedVertices[i] = true;
                selectedVertices[*j] = true;
                auxX = i;
                auxY = *j;
            }
            for (k = this->villages[*j].begin(); k != this->villages[*j].end(); ++k)
            {
                if (visited[*k] == false && (auxX == *j || auxY == *k || auxX == *k || auxY == *j))
                {
                    visited[*k] = true;
                }
            }
        }
    }

    return std::make_tuple(getAmountOfSelectedVertices(selectedVertices), selectedVertices);
}