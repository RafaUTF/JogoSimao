#include "Ente.h"

#include "Gerenciador_Grafico.h"

int Ente::cont(0);
Gerenciador_Grafico* Ente::pGG(0);


Ente::Ente() :id(cont++), corpo() {
	
	// Carregar a textura
	if (!textura.loadFromFile("q.png")) {
		std::cerr << "Erro ao carregar a textura QUADRADO!" << std::endl;
	}
	else {
		corpo.setTexture(textura);
	}
	corpo.setScale(100.f, 100.f);

}

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



Sprite Ente::getCorpo()
{
	return corpo;
}
