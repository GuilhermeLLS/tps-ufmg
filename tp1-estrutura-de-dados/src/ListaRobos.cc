#include "../include/ListaRobos.hpp"
#include "../include/Robo.hpp"
#include "../include/Command.hpp"

ListaRobos::ListaRobos()
{
    this->tamanho = 0;
}

void ListaRobos::SetRoboInactive(int pos)
{
    this->dados[pos].ativo = false;
}

void ListaRobos::ResetaRelatorio(int pos) {
    this->dados[pos].relatorio = "";
}

Robo ListaRobos::GetDado(int pos)
{
    if (pos > this->GetTamanho() || pos <= 0)
    {
        throw "ERRO: POSICAO INVALIDA!";
    }
    return this->dados[pos - 1];
}

void ListaRobos::SetDado(Robo dado, int pos)
{
    if (pos > this->GetTamanho() || pos <= 0)
    {
        throw "ERRO: POSICAO INVALIDA!";
    }
    this->dados[pos - 1] = dado;
}

bool ListaRobos::isRoboAtivo(int pos)
{
    return this->dados[pos].ativo == true;
}

int ListaRobos::GetTotalAliens(int pos)
{
    return this->dados[pos].totalAliens;
}

int ListaRobos::GetTotalRecursos(int pos)
{
    return this->dados[pos].totalRecursos;
}

void ListaRobos::InsereInicio(Robo dado)
{
    if (this->GetTamanho() == MAXTAM)
    {
        throw "ERRO: Lista cheia!";
    }
    if (this->Vazia())
    {
        this->dados[0] = dado;
        this->IncrementaTamanho();
    }
    else
    {
        this->IncrementaTamanho();
        for (int i = this->GetTamanho(); i > 0; i--)
        {
            this->dados[i] = this->dados[i - 1];
        }
        this->dados[0] = dado;
    }
}

void ListaRobos::InsereFinal(Robo dado)
{
    if (this->GetTamanho() == MAXTAM)
    {
        throw "ERRO: Lista cheia!";
    }
    int pos = this->GetTamanho();
    this->dados[pos] = dado;
    this->IncrementaTamanho();
}

int ListaRobos::GetTamanho()
{
    return this->tamanho;
}

void ListaRobos::IncrementaTamanho() { this->tamanho++; }
void ListaRobos::DecrementaTamanho() { this->tamanho--; }

void ListaRobos::InserePosicao(Robo dado, int pos)
{
    if (this->GetTamanho() == MAXTAM)
    {
        throw "ERRO: Lista cheia!";
    }
    if (pos > this->GetTamanho() || pos <= 0)
    {
        throw "ERRO: POSICAO INVALIDA!";
    }
    pos--;
    this->IncrementaTamanho();
    for (int i = this->GetTamanho(); i > pos; i--)
    {
        this->dados[i] = this->dados[i - 1];
    }
    this->dados[pos] = dado;
}

Robo ListaRobos::RemoveInicio()
{
    if (this->Vazia())
    {
        throw "ERRO: Lista vazia!";
    }

    Robo aux;
    aux = this->dados[0];
    for (int i = 1; i < this->GetTamanho(); i++)
    {
        this->dados[i - 1] = this->dados[i];
    }
    this->DecrementaTamanho();
    return aux;
}

Robo ListaRobos::RemoveFinal()
{
    if (this->Vazia())
    {
        throw "ERRO: Lista vazia!";
    }

    Robo aux;
    this->DecrementaTamanho();
    aux = this->dados[this->GetTamanho()];

    return aux;
}

Robo ListaRobos::RemovePosicao(int pos)
{
    if (this->Vazia())
    {
        throw "ERRO: Lista vazia!";
    }
    if (pos > this->GetTamanho() || pos <= 0)
    {
        throw "ERRO: POSICAO INVALIDA!";
    }

    Robo aux;
    aux = this->dados[pos - 1];

    for (int i = pos; i < this->GetTamanho(); i++)
    {
        this->dados[i - 1] = this->dados[i];
    }
    this->DecrementaTamanho();

    return aux;
}

void ListaRobos::SetRoboActive(int pos)
{
    this->dados[pos].ativo = true;
}

void ListaRobos::SetPosicoesRobo(int linha, int coluna, int pos)
{
    this->dados[pos].linhaX = linha;
    this->dados[pos].colunaY = coluna;
}

void ListaRobos::UpdateRelatorio(std::string message, int pos)
{
    this->dados[pos].SetRelatorio(message);
}

int ListaRobos::GetLinhaXRobo(int pos)
{
    return this->dados[pos].linhaX;
}

void ListaRobos::ImprimeRelatorio(int pos)
{
    this->dados[pos].ImprimeRelatorio();
}

int ListaRobos::GetColunaYRobo(int pos)
{
    return this->dados[pos].colunaY;
}

void ListaRobos::UpdateTotalRecursos(int valor, int pos)
{
    this->dados[pos].totalRecursos += valor;
}

void ListaRobos::UpdateTotalAliens(int valor, int pos)
{
    this->dados[pos].totalAliens += valor;
}

void ListaRobos::Imprime()
{
    for (int i = 0; i < this->GetTamanho(); i++)
    {
        std::cout << "--------------------" << std::endl;
        this->dados[i].ImprimeRobo();
    }
}

FilaEncadeada *ListaRobos::GetOrdensDeComando(int pos)
{
    return this->dados[pos].GetOrdensDeComando();
}

void ListaRobos::UpdateOrdensDeComando(int pos, Command item)
{
    this->dados[pos].OrdensDeComando->Enfilera(item);
}

Robo ListaRobos::Pesquisa(int numRobo)
{
    if (this->Vazia())
    {
        throw "ERRO: Lista vazia!";
    }
    Robo aux;

    for (int i = 0; i < this->GetTamanho(); i++)
    {
        if (numRobo == this->dados[i].numRobo)
        {
            aux = this->dados[i];
            break;
        }
    }
    return aux;
}