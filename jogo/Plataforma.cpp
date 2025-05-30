#include "Plataforma.h"

Plataforma::Plataforma() : Entidade(500, 450), tam_x(800.f), tam_y(100.f)
{
    corpo.setSize(sf::Vector2f(tam_x, tam_y));
    corpo.setFillColor(sf::Color::Yellow);
    corpo.setPosition(x, y);
}

Plataforma::~Plataforma(){}
