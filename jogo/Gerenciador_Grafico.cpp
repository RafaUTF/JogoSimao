#include "Gerenciador_Grafico.h"

Gerenciador_Grafico::Gerenciador_Grafico():
	janela(sf::VideoMode(DIREITA+50.f, CHAO), "janela",Style::Default),
	fundo()
{
	janela.setFramerateLimit(FPS);

	if (!textura.loadFromFile("fundo.png")) {
		std::cerr << "Erro ao carregar a textura BOSS!" << std::endl;
	}
	else {
		fundo.setTexture(textura);
	}
	fundo.setPosition(0.f, 0.f);
	fundo.scale(1.5f,1.5f);
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
}

void Gerenciador_Grafico::desenhar(Ente* pE)
{
	if (pE == NULL) {
		cout << "nao foi possivel desenhar o ente NULO" << endl;
		return;
	}
	janela.draw(pE->getCorpo());
}

void Gerenciador_Grafico::desenhar(const RectangleShape& retangulo)
{
	janela.draw(retangulo);
}

void Gerenciador_Grafico::desenhaFundo()
{
	janela.draw(fundo);
}

void Gerenciador_Grafico::mostrar()
{
	janela.display();
}

void Gerenciador_Grafico::fechar()
{
	janela.close();
}

sf::RenderWindow& Gerenciador_Grafico::getWindow()
{
	return janela;
}

const bool Gerenciador_Grafico::aberta() const
{
	return janela.isOpen();
}

void Gerenciador_Grafico::clear()
{
	janela.clear();
}
