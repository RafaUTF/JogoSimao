#include "Plataforma.h"

Plataforma::Plataforma(Vector2f pos, float desloc) : Obstaculo(Vector2f(pos.x, pos.y + desloc)), deslocamento(desloc)
{
	corpo.setSize(Vector2f(32.f, 32.f));
	centralizarEntidade();
	if (!textura.loadFromFile("plataforma.png")) {
		std::cerr << "Erro ao carregar a textura plataforma!" << std::endl;
	}
	else {
		corpo.setTexture(&textura);
	}
	//corpo.setFillColor(sf::Color::Transparent);
}


Plataforma::~Plataforma() {
	//cout << "destrutora plataforma" << endl;
}

void Plataforma::executar()
{
	//?
}

void Plataforma::obstacular(Personagem* p, int d)
{
	if (!p) return;
	p->zerarPulo();

	if (d == 1) {
		p->getVel().y = 0.f;
		p->getCorpo().setPosition(
			p->getcm().x,
			getcm().y + p->getRaio().y + getRaio().y
		);
	}
	if (d == 4) {
		p->setChao(true);
		p->getVel().y = 0.f;
		p->getCorpo().setPosition(
			p->getcm().x,
			getcm().y - p->getRaio().y - getRaio().y
		);
	}
	if (d == 2) {
		p->getVel().x = 0.f;
		p->getCorpo().setPosition(
			getcm().x + p->getRaio().x + getRaio().x,
			p->getcm().y
		);
	}
	if (d == 3) {
		p->getVel().x = 0.f;
		p->getCorpo().setPosition(
			getcm().x - p->getRaio().x - getRaio().x,
			p->getcm().y
		);
	}
}
