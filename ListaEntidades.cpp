#include "ListaEntidades.h"

ListaEntidades::ListaEntidades(): LEs(), it()
{
	LEs.clear();
	primeiro();
}

ListaEntidades::~ListaEntidades()
{
	for (Lista<Entidade*>::iterator it = LEs.begin();it != LEs.end();++it) {
		if (*it) {
			delete* it;
			*it = NULL;
		}
	}
	LEs.clear();
}

void ListaEntidades::incluir(Entidade* pE)
{
	if (pE)
		LEs.push_back(pE);
	else
		cout << "ponteiro nulo nao inserido" << endl;
}

void ListaEntidades::percorrer() {
	for (Lista<Entidade*>::iterator it = LEs.begin(); it != LEs.end(); ++it) {
		if (*it && *it != nullptr) { // Check for NULL and invalid pointers
			(*it)->executar();
		}
	}
}

void ListaEntidades::desenhar()
{
	for (Lista<Entidade*>::iterator it = LEs.begin();it != LEs.end();++it) {
		if (*it) {
			(*it)->desenhar(static_cast<Ente*>(*it));
		}
	}
}

Entidade* ListaEntidades::getAtual()
{
	return *it;
}

void ListaEntidades::primeiro()
{
	it = LEs.begin();
}

bool ListaEntidades::fim()
{
	return it == LEs.end();
}

void ListaEntidades::operator++()
{
	if (fim())
		cout << "Passou do final de LEs em ListaEntidades!" << endl;
	else
		++it;
}

void ListaEntidades::retirar(Entidade* pE)
{
	if (pE == NULL) {
		cout << "ponteiro nulo nao retirado" << endl;
		return;
	}
	if (LEs.remove(pE)) {
		cout << "ponteiro retirado" << endl;
	}
	else {
		cout << "ponteiro nao encontrado em LEs(nao retirado)" << endl;
	}
}

