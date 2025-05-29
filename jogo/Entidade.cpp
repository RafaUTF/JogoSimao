#include "Entidade.h"

Entidade::Entidade():x(20.f),y(20.f), corpo()
{
}
Entidade::~Entidade()
{
}

float Entidade::getXcm()
{
    return corpo.getPosition().x + corpo.getSize().x / 2;
}
float Entidade::getYcm()
{
    return corpo.getPosition().y + corpo.getSize().y / 2;
}

float Entidade::getRaioX()
{
    return corpo.getSize().x / 2;
}

float Entidade::getRaioY()
{
    return corpo.getSize().y / 2;
}

sf::RectangleShape Entidade::getCorpo()
{
    return corpo;
}
