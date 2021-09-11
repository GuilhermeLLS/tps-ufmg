#include "../include/ArvoreBinaria.hpp"

ArvoreBinaria::ArvoreBinaria()
{
    root = NULL;
}

ArvoreBinaria::~ArvoreBinaria()
{
    destruirArvore();
}

void ArvoreBinaria::destruirArvore(TipoNo *leaf)
{
    if (leaf != NULL)
    {
        destruirArvore(leaf->esq);
        destruirArvore(leaf->dir);
        delete leaf;
    }
}

void ArvoreBinaria::inserir(std::string key, TipoNo *leaf)
{

    if (key < leaf->dado)
    {
        if (leaf->esq != NULL)
        {
            inserir(key, leaf->esq);
        }
        else
        {
            leaf->esq = new TipoNo;
            leaf->esq->dado = key;
            leaf->esq->esq = NULL;
            leaf->esq->dir = NULL;
        }
    }
    else if (key > leaf->dado)
    {
        if (leaf->dir != NULL)
        {
            inserir(key, leaf->dir);
        }
        else
        {
            leaf->dir = new TipoNo;
            leaf->dir->dado = key;
            leaf->dir->dir = NULL;
            leaf->dir->esq = NULL;
        }
    }
}

void ArvoreBinaria::inserir(std::string key)
{
    if (root != NULL)
    {
        inserir(key, root);
    }
    else
    {
        root = new TipoNo;
        root->dado = key;
        root->esq = NULL;
        root->dir = NULL;
    }
}

int even_random_number()
{
    return 2 * (rand() % 5);
}

int odd_random_number()
{
    return even_random_number() + 1;
}

TipoNo *ArvoreBinaria::procurar(std::string key, TipoNo *leaf)
{
    if (leaf != NULL)
    {
        if (key == leaf->dado)
        {
            return leaf;
        }
        if (key < leaf->dado)
        {
            std::cout << odd_random_number();
            return procurar(key, leaf->esq);
        }
        else
        {
            std::cout << even_random_number();
            return procurar(key, leaf->dir);
        }
    }
    else
    {
        return NULL;
    }
}

TipoNo *ArvoreBinaria::procurar(std::string key)
{
    return procurar(key, root);
}

void ArvoreBinaria::destruirArvore()
{
    destruirArvore(root);
}

void ArvoreBinaria::decodificar(std::string code)
{
    std::regex expression("(x\\d{1,}|x)");
    std::regex_token_iterator<std::string::iterator> result(code.begin(), code.end(), expression);
    std::regex_token_iterator<std::string::iterator> end;

    TipoNo *aux = this->root;
    std::string finalResult = "";
    while (result != end)
    {
        std::string resultString = *result++;
        if (resultString == "x")
        {
            finalResult += aux->dado;
        }
        else
        {
            std::string parsedString = resultString.replace(0, 1, "");
            for (char caractere : parsedString)
            {
                int charNumber = (int)caractere - 48;
                aux = charNumber % 2 == 0 ? aux->dir : aux->esq;
            }
            finalResult += aux->dado;
        }
        aux = this->root;
    }
    std::cout << finalResult;
}