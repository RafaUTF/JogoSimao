#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

class TeiaAranha : public Obstaculo
{
private:
	int dano;

public:
	TeiaAranha(Vector2f pos = (Vector2f(0.f, 0.f)));
	~TeiaAranha();
	void obstacular(Personagem* p = NULL, int d=0);
	void executar();

	std::string getTipo() const { return "TeiaAranha"; }

};

