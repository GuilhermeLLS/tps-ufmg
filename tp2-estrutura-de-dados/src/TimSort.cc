#include "../include/Dados.hpp"
#include "../include/MergeSort.hpp"
#include "../include/TimSort.hpp"

const int RUN = 256;

void insertionSort(Dados conjunto[], int esquerda, int direita)
{
    for (int i = esquerda + 1; i <= direita; i++)
    {
        Dados temp = conjunto[i];
        int j = i - 1;
        while (j >= esquerda && conjunto[j].distancia > temp.distancia)
        {
            conjunto[j + 1] = conjunto[j];
            j--;
        }
        conjunto[j + 1] = temp;
    }
}

TimSort::TimSort(Dados *conjunto, int size)
{
    this->conjuntoClasse = conjunto;
    this->size = size;
}

std::tuple<Dados *, clock_t> TimSort::sort()
{
    clock_t time = clock();
    this->timSort(this->conjuntoClasse, this->size);
    time = clock() - time;
    return {this->conjuntoClasse, time};
}

void TimSort::timSort(Dados *conjunto, int size)
{
    MergeSort mergeSorter = MergeSort(conjunto, size);

    for (int i = 0; i < size; i += RUN)
        insertionSort(conjunto, i, std::min((i + 31), (size - 1)));

    for (int chunkSize = RUN; chunkSize < size;
         chunkSize = 2 * chunkSize)
    {

        for (int esquerda = 0; esquerda < size;
             esquerda += 2 * chunkSize)
        {

            int meio = esquerda + chunkSize - 1;
            int direita = std::min((esquerda + 2 * chunkSize - 1),
                                 (size - 1));
            
            // checa se ocorre um out of bounds error (meio >= direita) => isso implica que meio > tamanho do array
            if (meio >= direita) {
                int diff = meio - direita;
                int avg = (direita - esquerda) / 2;
                meio = meio - diff - avg;
            }

            mergeSorter.merge(conjunto, esquerda, meio, direita);
        }
    }
}