#include <iostream>
#include <fstream>
#include <string>
#include "../include/ArvoreBinaria.hpp"

void readDataAndExecuteCommands(std::string nomeArquivo)
{
    std::ifstream inputDados(nomeArquivo);
    ArvoreBinaria *binaria = new ArvoreBinaria();

    for (std::string line; getline(inputDados, line);)
    {
        char option = line[0];
        std::string parsedLine = line.replace(0, 3, "");
        if (option == 'A')
        {
            for (char c : parsedLine)
            {
                std::string convertedString(1, c);
                binaria->inserir(convertedString);
            }
        }
        if (option == 'C')
        {
            for (char c : parsedLine)
            {
                std::string convertedString(1, c);
                std::cout << 'x';
                binaria->procurar(convertedString);
            }
            std::cout << '\n';
        }
        if (option == 'D')
        {
            binaria->decodificar(parsedLine);
            std::cout << '\n';
        }
    }
}

int main(int argc, char *argv[])
{
    std::string nomeArquivo = argv[1];
    readDataAndExecuteCommands(nomeArquivo);

    return 0;
}