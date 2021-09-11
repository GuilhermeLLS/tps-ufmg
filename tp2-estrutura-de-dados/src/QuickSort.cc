#include "../include/Dados.hpp"
#include "../include/QuickSort.hpp"

QuickSort::QuickSort(Dados *conjunto, int size)
{
    this->conjuntoClasse = conjunto;
    this->size = size;
}

std::tuple<Dados *, clock_t> QuickSort::sort(std::string tipo)
{
    clock_t time;
    if (tipo == "pivo_mediana")
    {
        time = clock();
        quickSortMediana(this->conjuntoClasse, 0, this->size - 1);
        time = clock() - time;
    }
    else if (tipo == "pivo_meio")
    {
        time = clock();
        quickSort(this->conjuntoClasse, 0, this->size - 1);
        time = clock() - time;
    }
    else
    {
        throw std::runtime_error("Tipo não reconhecido. Escolha iterativo ou recursivo");
    }
    return {this->conjuntoClasse, time};
}

void QuickSort::partition(Dados *conjunto, int esquerda, int direita, int *indiceEsquerda, int *indiceDireita)
{
    Dados pivo, aux;
    *indiceEsquerda = esquerda;
    *indiceDireita = direita;
    pivo = conjunto[(*indiceEsquerda + *indiceDireita) / 2];
    while (*indiceEsquerda <= *indiceDireita)
    {
        while (pivo.distancia > conjunto[*indiceEsquerda].distancia)
        {
            (*indiceEsquerda)++;
        }
        while (pivo.distancia < conjunto[*indiceDireita].distancia)
        {
            (*indiceDireita)--;
        }
        if (*indiceEsquerda <= *indiceDireita)
        {
            aux = conjunto[*indiceEsquerda];
            conjunto[*indiceEsquerda] = conjunto[*indiceDireita];
            conjunto[*indiceDireita] = aux;
            (*indiceEsquerda)++;
            (*indiceDireita)--;
        }
    };
}

void QuickSort::quickSort(Dados *dados, int esquerda, int direita)
{
    int i, j;
    partition(dados, esquerda, direita, &i, &j);
    if (esquerda < j)
    {
        quickSort(dados, esquerda, j);
    }
    if (i < direita)
    {
        quickSort(dados, i, direita);
    }
}

int QuickSort::achaPivo(Dados *conjunto, int esq, int dir)
{
    Dados elemEsq = conjunto[esq];
    Dados elemMeio = conjunto[(esq + dir) / 2];
    Dados elemDir = conjunto[dir];

    if ((elemMeio.distancia < elemDir.distancia && elemMeio.distancia > elemEsq.distancia) || (elemMeio.distancia > elemDir.distancia && elemMeio.distancia < elemEsq.distancia))
        return (esq + dir) / 2;
    if ((elemEsq.distancia < elemMeio.distancia && elemEsq.distancia > elemDir.distancia) || (elemEsq.distancia > elemMeio.distancia && elemEsq.distancia < elemDir.distancia))
        return esq;
    if ((elemDir.distancia > elemMeio.distancia && elemDir.distancia < elemEsq.distancia) || (elemDir.distancia < elemMeio.distancia && elemDir.distancia > elemEsq.distancia))
        return dir;
    return (esq + dir) / 2;
}

void QuickSort::partitionMediana(Dados *conjunto, int esquerda, int direita, int *indiceEsquerda, int *indiceDireita)
{
    Dados pivo, aux;
    *indiceEsquerda = esquerda;
    *indiceDireita = direita;
    pivo = conjunto[achaPivo(conjunto, esquerda, direita)];
    while (*indiceEsquerda <= *indiceDireita)
    {
        while (pivo.distancia > conjunto[*indiceEsquerda].distancia)
        {
            (*indiceEsquerda)++;
        }
        while (pivo.distancia < conjunto[*indiceDireita].distancia)
        {
            (*indiceDireita)--;
        }
        if (*indiceEsquerda <= *indiceDireita)
        {
            aux = conjunto[*indiceEsquerda];
            conjunto[*indiceEsquerda] = conjunto[*indiceDireita];
            conjunto[*indiceDireita] = aux;
            (*indiceEsquerda)++;
            (*indiceDireita)--;
        }
    };
}

void QuickSort::quickSortMediana(Dados *dados, int esquerda, int direita)
{
    int i, j;
    partitionMediana(dados, esquerda, direita, &i, &j);
    if (esquerda < j)
    {
        quickSortMediana(dados, esquerda, j);
    }
    if (i < direita)
    {
        quickSortMediana(dados, i, direita);
    }
}
