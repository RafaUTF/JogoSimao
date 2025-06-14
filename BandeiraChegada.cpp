#include "BandeiraChegada.h"

BandeiraChegada::BandeiraChegada(Vector2f pos)
{
    corpo.setSize(sf::Vector2f(32.f, 32.f));
    centralizarEntidade();
    if (!textura.loadFromFile("bandeira.png")) {
        std::cerr << "Erro ao carregar a textura bandeira!" << std::endl;
    }
    else {
        corpo.setTexture(&textura);
    }
	terminoufase = false;
	danoso = false;
	cout << "Bandeira de chegada criada na posicao: " << pos.x << ", " << pos.y << endl;
}

BandeiraChegada::~BandeiraChegada()
{
}

void BandeiraChegada::executar()
{
    terminoufase = true;
}

void BandeiraChegada::obstacular(Jogador* p)
{
    executar();
}

void BandeiraChegada::causarDano(Jogador* p)
{
	// Bandeira não causa dano
}