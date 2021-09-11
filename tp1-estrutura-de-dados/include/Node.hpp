#ifndef NODE_HPP
#define NODE_HPP

#include "Command.hpp"

class Node{
    public:
        Node();
    private:
        Command dado;
        Node *proximo;

    friend class FilaEncadeada;
};


#endif