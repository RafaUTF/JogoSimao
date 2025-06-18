#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Ente.h"
#include "Entidade.h"

class Gerenciador_Grafico
{
private:
	//static Gerenciador_Grafico* pgg;


	sf::RenderWindow* janela;
	Sprite fundo;
	Texture textura;

	View camera;

	Gerenciador_Grafico();//tem que ser privada
public:
	~Gerenciador_Grafico();
	sf::RenderWindow* getWindow();
	const bool aberta() const;
	void clear();
	void desenhar(Ente* pE = NULL);
	void desenhar(const RectangleShape& retangulo);
	void desenhaFundo();
	void mostrar();
	void fechar();

	void moverCamera(Entidade* p1 = NULL, Entidade* p2 = NULL);

	static Gerenciador_Grafico* getInstancia();

	void setJanelaExterna(sf::RenderWindow* j);
};
