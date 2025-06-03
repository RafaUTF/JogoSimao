#pragma once
#include "Lista.h"
#include "Entidade.h"

class ListaEntidades {
private:
	Lista<Entidade*> LEs;
	Lista<Entidade*>::iterator it;

public:
	ListaEntidades();
	~ListaEntidades();
	void incluir(Entidade* pE=NULL);
	void percorrer();

	void desenhar();

	Entidade* getAtual();
	void primeiro();
	bool fim();
	void operator++();
};
