#ifndef MERGESORT_HPP
#define MERGESORT_HPP

#include <iostream>
#include <time.h>
#include <tuple>
#include "Dados.hpp"

class MergeSort
{
public:
    MergeSort(Dados *conjunto, int size);
    std::tuple<Dados *, clock_t> sort();

protected:
    void merge(Dados *conjunto, int esquerda, int meio, int direita);
    void mergeSort(Dados *conjunto, int esquerda, int direita);

private:
    Dados *conjuntoClasse;
    int size;

    friend class TimSort;
};

#endif