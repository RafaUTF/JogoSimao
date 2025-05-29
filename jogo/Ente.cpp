#include "Ente.h"

#include "Gerenciador_Grafico.h"

int Ente::cont(0);
Gerenciador_Grafico* Ente::pGG(0);

Ente::Ente():id(cont++), corpo() {}

Ente::~Ente()
{

}

void Ente::setpGG(Gerenciador_Grafico* p)
{
	pGG = p;
}

void Ente::desenhar(Ente* pE)
{
	if (pE == NULL) {
		cout << "falha ao desenhar ente" << endl;
		return;
	}
	pGG->desenhar(this);

}



sf::RectangleShape Ente::getCorpo()
{
	return corpo;
}
