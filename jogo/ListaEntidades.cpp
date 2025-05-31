#include "ListaEntidades.h"

ListaEntidades::ListaEntidades(): LEs()
{
	LEs.clear();
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

void ListaEntidades::percorrer()
{
	for (Lista<Entidade*>::iterator it = LEs.begin();it != LEs.end();++it) {
		if (*it) {
			(*it)->executar();
			//(*it)->desenhar(*it);
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

