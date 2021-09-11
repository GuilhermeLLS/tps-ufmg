#include "../include/Dados.hpp"
#include "../include/MergeSort.hpp"

MergeSort::MergeSort(Dados *conjunto, int size)
{
    this->conjuntoClasse = conjunto;
    this->size = size;
}

std::tuple<Dados *, clock_t>MergeSort::sort()
{
    clock_t time = clock();
    this->mergeSort(this->conjuntoClasse, 0, this->size - 1);
    time = clock() - time;
    return {this->conjuntoClasse, time};
}

void MergeSort::merge(Dados *conjunto, int esquerda, int meio, int direita)
{
    int tamanhoDivisaoEsquerda = meio - esquerda + 1;
    int tamanhoDivisaoDireita = direita - meio;

    Dados *divisaoEsquerda, *divisaoDireita;
    divisaoEsquerda = new Dados[tamanhoDivisaoEsquerda];
    divisaoDireita = new Dados[tamanhoDivisaoDireita];

    for (int i = 0; i < tamanhoDivisaoEsquerda; i++)
        divisaoEsquerda[i] = conjunto[esquerda + i];
    for (int j = 0; j < tamanhoDivisaoDireita; j++)
        divisaoDireita[j] = conjunto[meio + 1 + j];


    int indiceDivisaoEsquerda = 0;
    int indiceDivisaoDireita = 0;
    int indiceVetorCombinado = esquerda;

    while (indiceDivisaoEsquerda < tamanhoDivisaoEsquerda && indiceDivisaoDireita < tamanhoDivisaoDireita)
    {
        if (divisaoEsquerda[indiceDivisaoEsquerda].distancia <= divisaoDireita[indiceDivisaoDireita].distancia)
        {
            conjunto[indiceVetorCombinado] = divisaoEsquerda[indiceDivisaoEsquerda];
            indiceDivisaoEsquerda++;
        }
        else
        {
            conjunto[indiceVetorCombinado] = divisaoDireita[indiceDivisaoDireita];
            indiceDivisaoDireita++;
        }
        indiceVetorCombinado++;
    }

    while (indiceDivisaoEsquerda < tamanhoDivisaoEsquerda)
    {
        conjunto[indiceVetorCombinado] = divisaoEsquerda[indiceDivisaoEsquerda];
        indiceDivisaoEsquerda++;
        indiceVetorCombinado++;
    }

    while (indiceDivisaoDireita < tamanhoDivisaoDireita)
    {
        conjunto[indiceVetorCombinado] = divisaoDireita[indiceDivisaoDireita];
        indiceDivisaoDireita++;
        indiceVetorCombinado++;
    }
    delete[] divisaoDireita;
    delete[] divisaoEsquerda;
}

void MergeSort::mergeSort(Dados *conjunto, int esquerda, int direita)
{
    if (esquerda >= direita)
    {
        return; 
    }
    int meio = esquerda + (direita - esquerda) / 2;
    mergeSort(conjunto, esquerda, meio);
    mergeSort(conjunto, meio + 1, direita);
    merge(conjunto, esquerda, meio, direita);
}