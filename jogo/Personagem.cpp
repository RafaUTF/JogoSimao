#include "Personagem.h"

Personagem::Personagem() : num_vidas(10), corpo(), vy(0), vx(0),vg(0), agilidade(5.f) {
	//corpo.setPosition(100.f, 100.f);
	//corpo.setFillColor(sf::Color::White);
}


Personagem::~Personagem()
{
}

void Personagem::mover()
{
}

sf::RectangleShape Personagem::getCorpo()
{
	return corpo;
}

float Personagem::getXcm()
{
	return corpo.getPosition().x+corpo.getSize().x/2;
}

float Personagem::getYcm()
{
	return corpo.getPosition().y + corpo.getSize().y / 2;
}
