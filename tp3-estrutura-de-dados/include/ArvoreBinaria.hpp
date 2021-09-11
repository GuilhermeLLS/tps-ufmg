#ifndef ARVOREBINARIA_HPP
#define ARVOREBINARIA_HPP

#include <iostream>
#include <regex>
#include <string>
#include "./TipoNo.hpp"

class ArvoreBinaria
{
public:
	ArvoreBinaria();
	~ArvoreBinaria();

	void inserir(std::string key);
	TipoNo *procurar(std::string key);
	void destruirArvore();
    void decodificar(std::string code);

private:
	void destruirArvore(TipoNo *leaf);
	void inserir(std::string key, TipoNo *leaf);
	TipoNo *procurar(std::string key, TipoNo *leaf);

	TipoNo *root;
};

#endif