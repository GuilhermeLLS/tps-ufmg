#include "../include/Base.hpp"
#include "../include/ListaRobos.hpp"
#include "../include/FilaEncadeada.hpp"
#include "../include/Robo.hpp"

Base::Base()
{
    this->FilaDeOrdensDiretas = new FilaEncadeada();
    this->Robos = new ListaRobos();
    this->relatorio = "";
    this->totalRecursosBase = 0;
    this->totalAliensBase = 0;
}

void Base::SetBase(std::string **mapa, ListaRobos *Robos)
{
    this->mapa = mapa;
    this->FilaDeOrdensDiretas = new FilaEncadeada();
    this->Robos = Robos;
    this->relatorio = "";
    this->totalRecursosBase = 0;
    this->totalAliensBase = 0;
}

void Base::SetRobos(ListaRobos *Robos)
{
    this->Robos = Robos;
}

void Base::SetRelatorio(std::string relatorio)
{
    this->relatorio = this->relatorio + relatorio + ";";
}

void Base::SetMapa(std::string **mapa) { this->mapa = mapa; }

void Base::ResetaRelatorio() { this->relatorio = ""; }

void Base::ImprimeRelatorio()
{
    std::string delimiter = ";";
    std::string aux = this->relatorio;
    size_t pos = 0;
    std::string token;
    std::ofstream file("saida.txt", std::ofstream::app);
    while ((pos = aux.find(delimiter)) != std::string::npos)
    {
        token = aux.substr(0, pos);
        std::cout << token << std::endl;
        file << "BASE: " << token << "\n";
        aux.erase(0, pos + delimiter.length());
    }
    file.close();
}

int Base::GetTotalAliensBase() { return this->totalAliensBase; }

int Base::GetTotalRecursosBase() { return this->totalRecursosBase; }

void Base::UpdateTotalAliensBase(int valor)
{
    this->totalAliensBase += valor;
}

void Base::UpdateTotalRecursosBase(int valor)
{
    this->totalRecursosBase += valor;
}
