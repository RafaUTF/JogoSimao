#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

using std::cout;
using std::cin;
using std::endl;

#define CHAO 900.f
#define DIREITA 1750.f
#define ESQUERDA 50.f

#define PULO 10
#define ATRITO 0.5f
#define VISCOSO 0.2f
#define GRAVIDADE 0.5f
#define MAX_VEL 10.f//velocidade maxima

class Gerenciador_Grafico;

class Ente
{
protected:
	static int cont;
	int id;

	static Gerenciador_Grafico* pGG;

	Sprite corpo;//tirar o RectangleShape
	//RectangleShape corpo;
	Texture textura;
	//Figura* pFig;
	

public:
	Ente();//(Vector2f pos = (Vector2f(0.f, 0.f))); ENTIDADE!
	virtual ~Ente();
	//virtual void executar() = 0;
	static void setpGG(Gerenciador_Grafico* p);

	void desenhar(Ente* pE=NULL);

	Sprite getCorpo();

};
