#include "../include/Dados.hpp"
#include "../include/InsertionSort.hpp"

InsertionSort::InsertionSort(Dados *conjunto, int size)
{
    this->conjuntoClasse = conjunto;
    this->size = size;
}

std::tuple<Dados *, clock_t> InsertionSort::sort()
{
    clock_t time = clock();
    this->insertionSort(this->conjuntoClasse, this->size);
    time = clock() - time;
    return {this->conjuntoClasse, time};
}

void InsertionSort::insertionSort(Dados *conjunto, int size)
{
    Dados aux;
    int i, j;
    for (i = 1; i < size; i++)
    {
        aux = conjunto[i];
        j = i - 1;

        while (j >= 0 && conjunto[j].distancia > aux.distancia)
        {
            conjunto[j + 1] = conjunto[j];
            j = j - 1;
        }
        conjunto[j + 1] = aux;
    }
}