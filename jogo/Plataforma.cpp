#include "Plataforma.h"

Plataforma::Plataforma(Vector2f pos): Obstaculo(pos)
{
    corpo.setSize(Vector2f(400.f, 50.f));
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
