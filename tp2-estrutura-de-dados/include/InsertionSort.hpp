#ifndef INSERTIONSORT_HPP
#define INSERTIONSORT_HPP

#include <iostream>
#include <time.h>
#include <tuple>
#include "Dados.hpp"

class InsertionSort
{
public:
    InsertionSort(Dados conjunto[], int size);
    std::tuple<Dados*, clock_t> sort();

protected:
    void insertionSort(Dados conjunto[], int size);

private:
    Dados *conjuntoClasse;
    int size;
};


#endif