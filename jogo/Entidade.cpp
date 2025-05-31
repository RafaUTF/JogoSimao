#include "Entidade.h"

Entidade::Entidade(Vector2f pos): Ente()
{

    centralizarEntidade();
    corpo.setPosition(pos); // o centro do sprite ficará em pos

}
Entidade::~Entidade()
{
}
sf::Vector2f Entidade::getcm()
{
    return corpo.getPosition();
}

Vector2f Entidade::getRaio()
{
    sf::FloatRect bounds = corpo.getGlobalBounds();
    return sf::Vector2f(
        bounds.width / 2.f,
        bounds.height / 2.f
    );
}

void Entidade::centralizarEntidade()
{
    sf::FloatRect bounds = corpo.getLocalBounds();
    corpo.setOrigin(bounds.width / 2.f, bounds.height / 2.f); // origem no centro do sprite
}

