#include "Plataforma.h"

Plataforma::Plataforma(Vector2f pos): Obstaculo(pos)
{
    corpo.setSize(Vector2f(32.f, 32.f));
    centralizarEntidade();
    if (!textura.loadFromFile("plataforma.png")) {
        std::cerr << "Erro ao carregar a textura plataforma!" << std::endl;
    }
    else {
        corpo.setTexture(&textura);
		cout << "Plataforma criada!" << endl;
    }
    //corpo.setFillColor(sf::Color::Transparent);
}


Plataforma::~Plataforma(){
    //cout << "destrutora plataforma" << endl;
}

void Plataforma::executar()
{
    //?
}

void Plataforma::obstacular(Jogador* p)
{

}

void Plataforma::causarDano(Jogador* p)
{
    // Plataformas não causam dano
}