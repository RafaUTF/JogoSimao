#pragma once
#include "Ente.h"
class Entidade: public Ente
{
protected:
	sf::RectangleShape corpo;
	float x;
	float y;
public:
	Entidade();
	~Entidade();
	float getXcm();
	float getYcm();
	float getRaioX();
	float getRaioY();
	sf::RectangleShape getCorpo();
};

