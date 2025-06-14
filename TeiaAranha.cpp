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
}

void TeiaAranha::causarDano(Jogador* pJog)
{
}

void TeiaAranha::obstacular(Jogador* p)
{
    if (p) {
        p->reduzVelocidade(0.55f); // 
    }
}

void TeiaAranha::executar() {

}