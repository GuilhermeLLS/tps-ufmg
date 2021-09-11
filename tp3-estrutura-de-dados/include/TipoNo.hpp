
#ifndef TIPONO_HPP
#define TIPONO_HPP

#include <string>

struct TipoNo
{
    std::string dado;
    TipoNo *esq;
    TipoNo *dir;
};

#endif