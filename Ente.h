#pragma once
#include "stdafx.h"

class Gerenciador_Grafico;

class Ente
{
protected:
	static int cont;
	int id;

	static Gerenciador_Grafico* pGG;

	//Sprite corpo;//tirar o RectangleShape
	RectangleShape corpo;
	Texture textura;
	//Figura* pFig;
	

public:
	Ente();//(Vector2f pos = (Vector2f(0.f, 0.f))); ENTIDADE!
	virtual ~Ente();
	//virtual void executar() = 0;
	static void setpGG(Gerenciador_Grafico* p);

	void desenhar(Ente* pE=NULL);

	RectangleShape& getCorpo();

	void carregarTextura(const std::string& caminho);

};
