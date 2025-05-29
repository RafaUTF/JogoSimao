#pragma once
#include "Lista.h"
#include "Entidade.h"

class ListaEntidades {
private:
	Lista<Entidade*> LEs;
public:
	ListaEntidades();
	~ListaEntidades();
	void incluir(Entidade* pE=NULL);
	void percorrer();

	void desenhar();
};
