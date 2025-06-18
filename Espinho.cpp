#include "Espinho.h"

Espinho::Espinho(Vector2f pos) : Obstaculo(pos), dano(1)
{
    danoso = true;
    corpo.setSize(sf::Vector2f(32.f, 32.f));
    centralizarEntidade();
    if (!textura.loadFromFile("espinho.png")) {
        std::cerr << "Erro ao carregar a textura espinho!" << std::endl;
    }
    else {
        corpo.setTexture(&textura);
		cout << "construtora espinho" << endl;
    }
}

Espinho::~Espinho()
{
    cout << "destrutora espinho" << endl;
}

void Espinho::causarDano(Personagem* p)
{
    if (p != NULL) {
        p->operator--();
		cout << "Jogador atingido por espinho" << endl;
    }
}

void Espinho::obstacular(Personagem* p,int d)
{
    
	if (d == 1) {
		p->getVel().y = 0.f;
		p->getCorpo().setPosition(
			p->getcm().x,
			getcm().y + p->getRaio().y + getRaio().y+ELASTICIDADE_ESPINHO
		);
	}
	if (d == 4) {
		p->getVel().y = 0.f;
		p->getCorpo().setPosition(
			p->getcm().x,
			getcm().y - p->getRaio().y - getRaio().y - ELASTICIDADE_ESPINHO
		);
	}
	if (d == 2) {
		p->getVel().x = 0.f;
		p->getCorpo().setPosition(
			getcm().x + p->getRaio().x + getRaio().x+ ELASTICIDADE_ESPINHO,
			p->getcm().y
		);
	}
	if (d == 3) {
		p->getVel().x = 0.f;
		p->getCorpo().setPosition(
			getcm().x - p->getRaio().x - getRaio().x- ELASTICIDADE_ESPINHO,
			p->getcm().y
		);
	}

	causarDano(p);
}

void Espinho::executar() {

}