#include "Plataforma.h"

Plataforma::Plataforma(Vector2f pos): Obstaculo(pos)
{
    corpo.setSize(Vector2f(32.f, 32.f));
    centralizarEntidade();
    corpo.setFillColor(Color::Yellow);
}


Plataforma::~Plataforma(){}

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