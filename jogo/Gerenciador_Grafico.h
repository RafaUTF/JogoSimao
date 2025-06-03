#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Ente.h"

class Gerenciador_Grafico
{
private:
	static Gerenciador_Grafico* pgg;

	sf::RenderWindow janela;
	Sprite fundo;
	Texture textura;


	Gerenciador_Grafico();//tem que ser privada
public:
	~Gerenciador_Grafico();
	sf::RenderWindow& getWindow();
	const bool aberta() const;
	void clear();
	void desenhar(Ente* pE = NULL);
	void desenhar(const RectangleShape& retangulo);
	void desenhaFundo();
	void mostrar();
	void fechar();
	
	static Gerenciador_Grafico* getInstancia();
};

