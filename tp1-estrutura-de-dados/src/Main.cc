#include <fstream>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include <regex>
#include "../include/Command.hpp"
#include "../include/FilaEncadeada.hpp"
#include "../include/ListaRobos.hpp"
#include "../include/Robo.hpp"
#include "../include/Base.hpp"

bool temOrdemDireta(std::string linha)
{
    std::regex reg("(\\bATIVAR\\b|\\bEXECUTAR\\b|\\bRELATORIO\\b|\\bRETORNAR\\b)(.*)");
    return std::regex_match(linha, reg);
}

std::string **LerPreencherMapa(std::string caminhoArquivoMapa)
{
    std::ifstream mapInput(caminhoArquivoMapa);
    std::string x, y;
    mapInput >> x >> y;
    int linhas = stoi(x);
    const int colunas = stoi(y);
    int i = 0, j = 0;
    std::string **map = new std::string*[linhas];

    for (int i = 0; i < linhas; i++)
    {
        map[i] = new std::string[colunas];        
    }
    

    // * READ FILE AND UPDATE MAP MATRIX.
    bool shouldUpdateI = false;
    for (std::string line; getline(mapInput, line);)
    {
        int len = line.length();
        for (int positions = 0; positions < len; positions++)
        {
            char caractere = line[positions];
            if (caractere != ' ')
            {
                shouldUpdateI = true;
                map[i][j] = caractere;
                j++;
            }
        }
        j = 0;
        if (shouldUpdateI)
        {
            i++;
        }
    }
    return map;
}

void ExecutarOrdemDeComando(Base *BaseEspacial, Command item)
{
    int nRobs = item.GetNumRoboCommand();
    std::string nomeComando = item.GetNome();

    if (nomeComando == "MOVER" || nomeComando == "*MOVER")
    {
        int linha = item.GetLinhaX();
        int coluna = item.GetColunaY();
        BaseEspacial->Robos->SetPosicoesRobo(linha, coluna, nRobs);
        std::string elemInPosition = BaseEspacial->mapa[linha][coluna];
        if (elemInPosition == "O")
        {
            BaseEspacial->Robos->UpdateRelatorio("IMPOSSIVEL MOVER PARA (" + std::to_string(linha) + "," + std::to_string(coluna) + ")", nRobs);
        }
        else
        {
            BaseEspacial->Robos->UpdateRelatorio("MOVEU PARA (" + std::to_string(linha) + "," + std::to_string(coluna) + ")", nRobs);
        }
    }
    if (nomeComando == "COLETAR" || nomeComando == "*COLETAR")
    {
        int linha = BaseEspacial->Robos->GetLinhaXRobo(nRobs);
        int coluna = BaseEspacial->Robos->GetColunaYRobo(nRobs);
        std::string elemInPosition = BaseEspacial->mapa[linha][coluna];
        if (elemInPosition == "R")
        {
            BaseEspacial->Robos->UpdateRelatorio("RECURSOS COLETADOS EM (" + std::to_string(linha) + "," + std::to_string(coluna) + ")", nRobs);
            BaseEspacial->Robos->UpdateTotalRecursos(1, nRobs);
            BaseEspacial->mapa[linha][coluna] = ".";
        }
        else
        {
            BaseEspacial->Robos->UpdateRelatorio("IMPOSSIVEL COLETAR RECURSOS EM (" + std::to_string(linha) + "," + std::to_string(coluna) + ")", nRobs);
        }
    }
    if (nomeComando == "ELIMINAR" || nomeComando == "*ELIMINAR")
    {
        int linha = BaseEspacial->Robos->GetLinhaXRobo(nRobs);
        int coluna = BaseEspacial->Robos->GetColunaYRobo(nRobs);
        std::string elemInPosition = BaseEspacial->mapa[linha][coluna];
        if (elemInPosition == "H")
        {
            BaseEspacial->Robos->UpdateRelatorio("ALIEN ELIMINADO EM (" + std::to_string(linha) + "," + std::to_string(coluna) + ")", nRobs);
            BaseEspacial->Robos->UpdateTotalAliens(1, nRobs);
            BaseEspacial->mapa[linha][coluna] = ".";
        }
        else
        {
            BaseEspacial->Robos->UpdateRelatorio("IMPOSSIVEL ELIMINAR ALIEN EM (" + std::to_string(linha) + "," + std::to_string(coluna) + ")", nRobs);
        }
    }
}

void ExecutarOrdemDireta(Base *BaseEspacial, Command item)
{
    int nRobs = item.GetNumRoboCommand();
    std::string nomeOrdemDireta = item.GetNome();

    if (nomeOrdemDireta == "ATIVAR")
    {
        if (BaseEspacial->Robos->isRoboAtivo(nRobs))
        {

            BaseEspacial->SetRelatorio("ROBO " + std::to_string(nRobs) + " JA ESTA EM MISSAO");
            BaseEspacial->ImprimeRelatorio();
            BaseEspacial->ResetaRelatorio();
        }
        else
        {
            BaseEspacial->Robos->SetRoboActive(nRobs);
            BaseEspacial->SetRelatorio("ROBO " + std::to_string(nRobs) + " SAIU EM MISSAO");
            BaseEspacial->ImprimeRelatorio();
            BaseEspacial->ResetaRelatorio();
        }
    }
    else if (nomeOrdemDireta == "RELATORIO")
    {
        BaseEspacial->Robos->ImprimeRelatorio(nRobs);
    }
    else if (nomeOrdemDireta == "RETORNAR")
    {
        if (BaseEspacial->Robos->isRoboAtivo(nRobs))
        {
            BaseEspacial->Robos->SetRoboInactive(nRobs);
            BaseEspacial->UpdateTotalAliensBase(BaseEspacial->Robos->GetTotalAliens(nRobs));
            BaseEspacial->UpdateTotalRecursosBase(BaseEspacial->Robos->GetTotalRecursos(nRobs));
            BaseEspacial->SetRelatorio("ROBO " + std::to_string(nRobs) + " RETORNOU " + std::to_string(BaseEspacial->Robos->GetTotalAliens(nRobs)) + " ALIENS " + "RECURSOS " + std::to_string(BaseEspacial->Robos->GetTotalRecursos(nRobs)));
            BaseEspacial->Robos->UpdateTotalAliens(-BaseEspacial->Robos->GetTotalAliens(nRobs), nRobs);
            BaseEspacial->Robos->UpdateTotalRecursos(-BaseEspacial->Robos->GetTotalRecursos(nRobs), nRobs);
            BaseEspacial->Robos->ResetaRelatorio(nRobs);
        }
        else
        {
            BaseEspacial->SetRelatorio("ROBO " + std::to_string(nRobs) + "NAO ESTA EM MISSAO");
        }
        BaseEspacial->ImprimeRelatorio();
        BaseEspacial->ResetaRelatorio();
    }
    else if (nomeOrdemDireta == "EXECUTAR")
    {
        FilaEncadeada *Comandos = BaseEspacial->Robos->GetOrdensDeComando(nRobs);
        while (!Comandos->Vazia())
        {
            Command aux = Comandos->Desenfilera();
            ExecutarOrdemDeComando(BaseEspacial, aux);
        }
    }
}

void LerExecutarComandos(Base *BaseEspacial, std::string caminhoArquivoComandos)
{
    std::ifstream commandInput(caminhoArquivoComandos);
    bool isOrdemDireta;
    for (std::string line; getline(commandInput, line);)
    {
        int hasPositions = 0;
        Command item = Command();
        std::istringstream stringQuebrada(line);
        std::string aux;
        isOrdemDireta = temOrdemDireta(line);
        while (getline(stringQuebrada, aux, ' '))
        {
            // nome do comando
            if (hasPositions == 0)
            {
                item.setNome(aux);
                bool temPrioridade = aux.at(0) == '*';
                if (temPrioridade)
                {
                    item.SetPrioridade(true);
                }
                else
                {
                    item.SetPrioridade(false);
                }
                hasPositions++;
                continue;
            }
            // numero do robo
            if (hasPositions == 1)
            {
                item.setNumRobo(std::stoi(aux));
                hasPositions++;
                continue;
            }
            // coordenadas do comando (se existirem)
            if (hasPositions == 2)
            {
                std::istringstream coordenadas(aux);
                std::string coorAux;
                std::regex achaParenteses("(\\(|\\))");
                bool isLinha = true;
                int linhaX;
                int colunaY;
                while (getline(coordenadas, coorAux, ','))
                {
                    std::string result = std::regex_replace(coorAux, achaParenteses, "");
                    if (isLinha)
                    {
                        linhaX = stoi(result);
                        isLinha = false;
                    }
                    else
                    {
                        colunaY = stoi(result);
                    }
                }
                item.setLinhaX(linhaX);
                item.setColunaY(colunaY);
                hasPositions++;
                continue;
            }
            else
            {
                item.setLinhaX(-1);
                item.setColunaY(-1);
                hasPositions++;
            }
        }
        if (isOrdemDireta)
        {
            BaseEspacial->FilaDeOrdensDiretas->Enfilera(item);
            ExecutarOrdemDireta(BaseEspacial, item);
        }
        else
        {
            BaseEspacial->Robos->UpdateOrdensDeComando(item.GetNumRoboCommand(), item);
        }
    }
    BaseEspacial->SetRelatorio("TOTAL ALIENS " + std::to_string(BaseEspacial->GetTotalAliensBase()) + " RECURSOS " + std::to_string(BaseEspacial->GetTotalRecursosBase()));
    BaseEspacial->ImprimeRelatorio();
}

int main(int argc, char *argv[])
{
    std::string caminhoArquivoMapa(argv[1]);
    std::string caminhoArquivoComandos(argv[2]);

    std::string **map = LerPreencherMapa(caminhoArquivoMapa);
    std::cout << "problema no mapa" << std::endl;
    ListaRobos *ListaDeRobosAux = new ListaRobos();
    for (int i = 0; i < 50; i++)
    {
        Robo auxRobo = Robo();
        auxRobo.SetNumRobo(i);
        ListaDeRobosAux->InsereFinal(auxRobo);
    }

    Base *BaseEspacial = new Base();
    BaseEspacial->SetBase(map, ListaDeRobosAux);

    LerExecutarComandos(BaseEspacial, caminhoArquivoComandos);
    free(map);
    return 0;
}