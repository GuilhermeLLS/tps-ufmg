#ifndef LISTAROBOS_HPP
#define LISTAROBOS_HPP

#include "Robo.hpp"
#include "../include/FilaEncadeada.hpp"
#include "../include/Command.hpp"

class ListaRobos
{
public:
    ListaRobos();
    int GetTamanho();
    void IncrementaTamanho();
    void DecrementaTamanho();
    bool Vazia() { return tamanho == 0; };
    Robo GetDado(int pos);
    void SetRoboActive(int pos);
    void SetDado(Robo dado, int pos);
    void InsereInicio(Robo dado);
    void InsereFinal(Robo dado);
    void InserePosicao(Robo dado, int pos);
    Robo RemoveInicio();
    Robo RemoveFinal();
    Robo RemovePosicao(int pos);
    void Imprime();
    Robo Pesquisa(int chave);
    void SetPosicoesRobo(int linha, int coluna, int pos);
    void UpdateRelatorio(std::string message, int pos);
    int GetLinhaXRobo(int pos);
    int GetColunaYRobo(int pos);
    void UpdateTotalRecursos(int valor, int pos);
    void UpdateTotalAliens(int valor, int pos);
    bool isRoboAtivo(int pos);
    int GetTotalAliens(int pos);
    int GetTotalRecursos(int pos);
    FilaEncadeada *GetOrdensDeComando(int pos);
    void UpdateOrdensDeComando(int pos, Command item);
    void ImprimeRelatorio(int pos);
    void SetRoboInactive(int pos);
    void ResetaRelatorio(int pos);

    int tamanho;

private:
    static const int MAXTAM = 50;
    Robo dados[MAXTAM];
};

#endif