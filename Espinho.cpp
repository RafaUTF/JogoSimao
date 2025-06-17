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
    }
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