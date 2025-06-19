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
	void causarDano(Personagem* p);
	void obstacular(Personagem* p = NULL, int d = 0);
	void executar();

	std::string getTipo() const override { return "Espinho"; }

};