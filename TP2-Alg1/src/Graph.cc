#include "../include/Graph.hpp"

Graph::Graph(int numberOfAirports)
{
    this->numberOfAirports = numberOfAirports;
    airports = new std::list<int>[numberOfAirports];
}

Graph *Graph::transpose()
{
    Graph *g = new Graph(this->numberOfAirports);
    for (int v = 0; v < this->numberOfAirports; v++)
    {
        std::list<int>::iterator i;
        for (i = this->airports[v].begin(); i != this->airports[v].end(); ++i)
        {
            g->airports[*i].push_back(v);
        }
    }
    return g;
}

void Graph::addPair(int from, int to)
{
    this->airports[from].push_back(to);
}

void Graph::dfsStack(int v, bool visited[], std::stack<int> &vertexStack)
{
    visited[v] = true;
    std::list<int>::iterator i;
    for (i = this->airports[v].begin(); i != this->airports[v].end(); ++i)
    {
        if (!visited[*i])
        {
            this->dfsStack(*i, visited, vertexStack);
        }
    }

    vertexStack.push(v);
}

void Graph::checkOuterDegrees(int elem)
{
    for (unsigned int i = 0; i < this->scc.size(); ++i)
    {
        if (std::find(this->scc[i].begin(), this->scc[i].end(), elem) != this->scc[i].end())
        {
            this->grausOut[i] += 1;
        }
    }
}
void Graph::findSSCsAndGetDegrees()
{
    std::stack<int> vertexStack;
    bool *visited = new bool[this->numberOfAirports];
    this->initializeVisited(visited);

    for (int i = 0; i < this->numberOfAirports; ++i)
    {
        if (visited[i] == false)
        {
            this->dfsStack(i, visited, vertexStack);
        }
    }

    Graph *gr = this->transpose();
    this->initializeVisited(visited);

    int indexator = 0;
    while (vertexStack.empty() == false)
    {
        int v = vertexStack.top();
        vertexStack.pop();
        if (visited[v] == false)
        {
            this->initializeStorages();
            gr->dfsSsc(v, visited, indexator, scc);
            indexator++;
        }
    }
    this->innerOutterDegrees();
}

void Graph::dfsSsc(int v, bool visited[], int indexator, std::vector<std::vector<int>> &scc)
{
    visited[v] = true;
    scc[indexator].push_back(v);
    std::list<int>::iterator i;
    for (i = this->airports[v].begin(); i != this->airports[v].end(); ++i)
    {
        if (!visited[*i])
        {
            this->dfsSsc(*i, visited, indexator, scc);
        }
    }
}

void Graph::innerOutterDegrees()
{
    std::vector<int>::iterator j;
    std::list<int>::iterator k;
    for (unsigned int i = 0; i < this->scc.size(); ++i)
    {
        for (j = this->scc[i].begin(); j != this->scc[i].end(); ++j)
        {
            for (k = this->airports[*j].begin(); k != this->airports[*j].end(); ++k)
            {
                if (std::find(this->scc[i].begin(), this->scc[i].end(), *k) == this->scc[i].end())
                {
                    this->grausIn[i] += 1;
                    this->checkOuterDegrees(*k);
                }
            }
        }
    }
}

void Graph::minimalAddition()
{
    int inD = 0, outD = 0;
    for (unsigned int i = 0; i < this->grausIn.size(); ++i)
    {
        if (this->grausIn[i] == 0)
        {
            inD++;
        }
        if (this->grausOut[i] == 0)
        {
            outD++;
        }
    }
    std::cout << std::max(outD, inD) << std::endl;
}

void Graph::initializeVisited(bool visited[])
{
    for (int i = 0; i < this->numberOfAirports; ++i)
    {
        visited[i] = false;
    }
}

void Graph::initializeStorages()
{
    this->scc.push_back({});
    this->grausIn.push_back(0);
    this->grausOut.push_back(0);
}