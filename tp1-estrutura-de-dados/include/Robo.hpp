#ifndef ROBO_HPP
#define ROBO_HPP

#include <string>
#include <iostream>
#include <fstream>

#include "../include/FilaEncadeada.hpp"

class Robo
{
public:
    Robo();
    void SetRobo(int numRobo, int linhaX, int colunaY, bool ativo, std::string relatorio, int totalRecursos, int totalAliens, FilaEncadeada *OrdensDeComando);
    void SetNumRobo(int num);
    void SetCoordenadas(int linhaX, int colunaY);
    void SetAtivo();
    void SetRecursos();
    void SetAliens();
    void SetRelatorio(std::string relatorio);
    void ImprimeRelatorio();
    int GetNumRobo();
    void ImprimeRobo();
    FilaEncadeada *GetOrdensDeComando();
    void SetOrdensDeComando(FilaEncadeada *ordensDeComando);

protected:
    int numRobo;
    int linhaX;
    int colunaY;
    bool ativo;
    std::string relatorio;
    int totalRecursos;
    int totalAliens;
    FilaEncadeada *OrdensDeComando;

    friend class ListaRobos;
};

#endif
