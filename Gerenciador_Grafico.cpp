#include "Gerenciador_Grafico.h"


Gerenciador_Grafico::Gerenciador_Grafico() :
	janela(sf::VideoMode(DIREITA, CHAO), "janela", Style::Default),
	fundo(),
	camera(sf::FloatRect(0, 0, static_cast<int>(DIREITA), static_cast<int>(CHAO)))
{
	cout << "Gerenciador_Grafico criado" << endl;
	janela.setFramerateLimit(FPS);

	if (!textura.loadFromFile("fundo.png")) {
		std::cerr << "Erro ao carregar a textura BOSS!" << std::endl;
	}
	else {
		fundo.setTexture(textura);
	}
	fundo.setPosition(0.f, 0.f);
	fundo.scale(1.5f, 1.5f);
}

Gerenciador_Grafico::~Gerenciador_Grafico()
{
	cout << "destrutora Gerenciador_Grafico" << endl;

}

void Gerenciador_Grafico::desenhar(Ente* pE)
{
	if (pE == nullptr) {
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

void Gerenciador_Grafico::moverCamera(Entidade* p1, Entidade* p2)
{
	float larguraJanela = camera.getSize().x;
	float larguraCenario = TAMANHOTOTALLATERAL;

	float centroX;
	if (p2) {
		centroX = (p1->getcm().x + p2->getcm().x) / 2.f;
	}
	else {
		centroX = p1->getcm().x;
	}

	float minCentro = larguraJanela / 2.f;
	float maxCentro = larguraCenario - larguraJanela / 2.f;

	if (centroX < minCentro)
		centroX = minCentro;
	if (centroX > maxCentro)
		centroX = maxCentro;

	camera.setCenter(Vector2f(centroX, CHAO / 2.f));
	janela.setView(camera);
}



Gerenciador_Grafico* Gerenciador_Grafico::getInstancia() {
	static Gerenciador_Grafico instancia;
	return &instancia;
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