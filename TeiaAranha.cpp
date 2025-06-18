#include "TeiaAranha.h"

TeiaAranha::TeiaAranha(Vector2f pos) : Obstaculo(pos), dano(1)
{
	danoso = false;
	corpo.setSize(sf::Vector2f(32.f, 32.f));
	centralizarEntidade();
	if (!textura.loadFromFile("teiaaranha.png")) {
		std::cerr << "Erro ao carregar a textura plataforma!" << std::endl;
	}
	else {
		corpo.setTexture(&textura);
	}
	//corpo.setFillColor(sf::Color::Transparent);
}

TeiaAranha::~TeiaAranha()
{
	cout << "destrutora teia" << endl;
}


void TeiaAranha::obstacular(Personagem* p, int d)
{
	if (p) {
		p->reduzVelocidade(0.55f); // 
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
}

void TeiaAranha::executar() {

}