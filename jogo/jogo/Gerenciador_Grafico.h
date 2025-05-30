#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Ente.h"

class Gerenciador_Grafico
{
private:
	sf::RenderWindow janela;
public:
	Gerenciador_Grafico();
	~Gerenciador_Grafico();
	void desenhar(Ente* pE = NULL);
	sf::RenderWindow& getWindow();
};

