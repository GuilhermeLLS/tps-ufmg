#include <regex>
#include "../include/FilaEncadeada.hpp"
#include "../include/Node.hpp"

FilaEncadeada::FilaEncadeada()
{
    this->frente = new Node();
    this->fim = this->frente;
    this->tamanho = 0;
}

void FilaEncadeada::Enfilera(Command dado)
{
    Node *novo;
    novo = new Node();

    if (Vazia())
    {
        this->frente->proximo = novo;
        novo->proximo = NULL;
    }
    if (dado.GetPrioridade())
    {
        // std::cout << "prioridade" << std::endl;
        // novo->dado = dado;
        // novo->proximo = frente->proximo;
        // this->frente->proximo = novo;
        novo->dado = dado;
        novo->proximo = this->frente->proximo;
        this->frente->proximo = novo;
        // Node *aux = new Node();
        // aux->dado = dado;
        // this->frente->proximo = aux;
    }
    else
    {
        novo->dado = dado;
        this->fim->proximo = novo;
        this->fim = novo;
    }
    this->tamanho++;
}

Command FilaEncadeada::Desenfilera()
{
    if (Vazia())
    {
        throw "ERRO: Fila esta vazia!";
    }
    Command aux;
    Node *p;

    p = this->frente->proximo;
    this->frente->proximo = p->proximo;

    aux = p->dado;
    delete p;
    this->tamanho--;

    return aux;
}

void FilaEncadeada::Limpa()
{
    if (Vazia())
    {
        throw "ERRO: Fila esta vazia!";
    }
    while (!Vazia())
    {
        Desenfilera();
    }
}
