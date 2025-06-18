#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

class Espinho : public Obstaculo
{
private:
	int dano;

public:
	Espinho(Vector2f pos = (Vector2f(0.f, 0.f)));
	~Espinho();
	void causarDano(Jogador* pJog);
	void obstacular(Jogador* p = NULL);
	void executar();

	std::string getTipo() const{ return "Espinho"; }

};

