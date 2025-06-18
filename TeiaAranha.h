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
	void causarDano(Jogador* pJog);
	void obstacular(Jogador* p = NULL);
	void executar();

	std::string getTipo() const { return "TeiaAranha"; }

};

