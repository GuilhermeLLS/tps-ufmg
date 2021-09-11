#include <fstream>
#include <string>
#include <iostream>
#include <time.h>
#include "../include/Dados.hpp"
#include "../include/QuickSort.hpp"
#include "../include/InsertionSort.hpp"
#include "../include/MergeSort.hpp"
#include "../include/TimSort.hpp"

void imprimirConjunto(Dados *conjunto, int tamanho, clock_t execTime, std::string algoType)
{
    std::cout << "Executando " << algoType << "..." << std::endl;
    std::ofstream saida("saida.txt", std::ofstream::in);
    for (int i = tamanho - 1; i > 0; i--)
    {
        saida << conjunto[i].nome << ", " << conjunto[i].distancia << "\n";
    }
    saida.close();
    std::cout << "Execution time: " << ((double)execTime) / ((CLOCKS_PER_SEC / 1000)) << "ms" << std::endl;
}

int main(int argc, char *argv[])
{
    std::string nomeArquivo = argv[1];
    int linhasParaLer = atoi(argv[2]);

    Dados conjunto[linhasParaLer];
    std::ifstream dadosInput(nomeArquivo);
    int i = linhasParaLer;
    while (i > 0)
    {
        std::string line;
        getline(dadosInput, line);
        std::string delimiter = " ";
        size_t pos = 0;
        std::string token;
        while ((pos = line.find(delimiter)) != std::string::npos)
        {
            token = line.substr(0, pos);
            conjunto[i - 1].nome = token;
            line.erase(0, pos + delimiter.length());
        }
        conjunto[i - 1].distancia = stoi(line);
        i--;
    }

    std::string escolha;
    std::cout << "0- QuickSort Pivo Meio\n"
              << "1- QuickSort Pivo Mediana\n"
              << "2- InsertionSort\n"
              << "3- MergeSort\n"
              << "4- TimSort\n"
              << "Aperte qualquer outra tecla para sair" << std::endl;
    std::cin >> escolha;

    switch (stoi(escolha))
    {
    case 0:
    {
        QuickSort *sorter = new QuickSort(conjunto, linhasParaLer);
        Dados *auxQuickMeio;
        clock_t execTimeQuickPivoMeio;
        std::tie(auxQuickMeio, execTimeQuickPivoMeio) = sorter->sort("pivo_meio");
        imprimirConjunto(auxQuickMeio, linhasParaLer, execTimeQuickPivoMeio, "Quicksort Pivo Meio");
        delete sorter;
        break;
    }
    case 1:
    {
        QuickSort *pivoMedianaSorter = new QuickSort(conjunto, linhasParaLer);
        Dados *auxQuickPivoMediana;
        clock_t execTimeQuickPivoMediana;
        std::tie(auxQuickPivoMediana, execTimeQuickPivoMediana) = pivoMedianaSorter->sort("pivo_mediana");
        imprimirConjunto(auxQuickPivoMediana, linhasParaLer, execTimeQuickPivoMediana, "Quicksort Pivo Mediana");
        delete pivoMedianaSorter;
        break;
    }
    case 2:
    {
        InsertionSort *inSorter = new InsertionSort(conjunto, linhasParaLer);
        Dados *auxIns;
        clock_t execTimeInsertion;
        std::tie(auxIns, execTimeInsertion) = inSorter->sort();
        imprimirConjunto(auxIns, linhasParaLer, execTimeInsertion, "InsertionSort");
        delete inSorter;
        break;
    }
    case 3:
    {
        MergeSort *mergeSorter = new MergeSort(conjunto, linhasParaLer);
        Dados *auxMergeSort;
        clock_t execTimeMerge;
        std::tie(auxMergeSort, execTimeMerge) = mergeSorter->sort();
        imprimirConjunto(auxMergeSort, linhasParaLer, execTimeMerge, "MergeSort");
        delete mergeSorter;
        break;
    }
    case 4:
    {
        TimSort *timSorter = new TimSort(conjunto, linhasParaLer);
        Dados *auxTimSort;
        clock_t execTimeTim;
        std::tie(auxTimSort, execTimeTim) = timSorter->sort();
        imprimirConjunto(auxTimSort, linhasParaLer, execTimeTim, "TimSort");
        delete timSorter;
    }
    default:
    {
        std::cout << "Saindo..." << std::endl;
        break;
    }
    }

    return 0;
}