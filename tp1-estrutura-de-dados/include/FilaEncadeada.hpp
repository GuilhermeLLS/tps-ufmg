#ifndef FILAENCADEADA_HPP
#define FILAENCADEADA_HPP

#include "Node.hpp"

class FilaEncadeada
{
public:
    FilaEncadeada();
    int GetTamanho() { return tamanho; };
    bool Vazia() { return tamanho == 0; };
    void Enfilera(Command dado);
    Command Desenfilera();
    void Limpa();

protected:
    int tamanho;

private:
    Node *frente;
    Node *fim;
};

#endif
