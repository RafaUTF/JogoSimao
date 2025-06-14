#include "TeiaAranha.h"

TeiaAranha::TeiaAranha(Vector2f pos) : Obstaculo(pos), dano(1)
{
    danoso = false;
    corpo.setSize(sf::Vector2f(32.f, 32.f));
	centralizarEntidade();
    corpo.setFillColor(sf::Color::Blue);
}

TeiaAranha::~TeiaAranha()
{
    cout << "destrutora teia" << endl;
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