#ifndef BASE_HPP
#define BASE_HPP

#include "../include/FilaEncadeada.hpp"
#include "../include/ListaRobos.hpp"

class Base
{
public:
    Base();
    void SetBase(std::string **mapa, ListaRobos *Robos);
    void SetRobos(ListaRobos *Robos);
    void SetMapa(std::string **mapa);
    void SetRelatorio(std::string relatorio);
    void ImprimeRelatorio();
    int GetTotalRecursosBase();
    int GetTotalAliensBase();
    void UpdateTotalAliensBase(int valor);
    void UpdateTotalRecursosBase(int valor);
    void ResetaRelatorio();

    ListaRobos *Robos;
    FilaEncadeada *FilaDeOrdensDiretas;
    std::string **mapa;
    std::string relatorio;
    int totalRecursosBase = 0;
    int totalAliensBase = 0;
};

#endif