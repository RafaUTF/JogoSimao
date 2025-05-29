#include "Gerenciador_Grafico.h"

Gerenciador_Grafico::Gerenciador_Grafico():
	janela(sf::VideoMode(1800, 900), "janela")
{
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
}

void Gerenciador_Grafico::desenhar(Ente* pE)
{
	janela.draw(pE->getCorpo());
}

sf::RenderWindow& Gerenciador_Grafico::getWindow()
{
	return janela;
}
