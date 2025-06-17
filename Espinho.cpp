#include "Espinho.h"

Espinho::Espinho(Vector2f pos) : Obstaculo(pos), dano(1)
{
    danoso = true;
    corpo.setSize(sf::Vector2f(32.f, 32.f));
    centralizarEntidade();
    //corpo.setFillColor(sf::Color::White);
    corpo.setFillColor(sf::Color::Transparent);
}

Espinho::~Espinho()
{
    cout << "destrutora espinho" << endl;
}

void Espinho::causarDano(Jogador* pJog)
{
    if (pJog != NULL) {
        pJog->operator--();
		cout << "Jogador atingido por espinho" << endl;
    }
}

void Espinho::obstacular(Jogador* p)
{
    causarDano(p);
}

void Espinho::executar() {

}