#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <iostream>
#include <time.h>
#include <tuple>
#include "Dados.hpp"

class QuickSort
{
public:
    QuickSort(Dados *conjunto, int size);
    std::tuple<Dados *, clock_t> sort(std::string tipo);

protected:
    int achaPivo(Dados *conjunto, int esquerda, int direita);
    void partition(Dados *conjunto, int esquerda, int direita, int *i, int *j);
    void partitionMediana(Dados *conjunto, int esquerda, int direita, int *i, int *j);
    void quickSort(Dados *conjunto, int esquerda, int direita);
    void quickSortMediana(Dados *conjunto, int esquerda, int direita);

private:
    Dados *conjuntoClasse;
    int size;
};

#endif