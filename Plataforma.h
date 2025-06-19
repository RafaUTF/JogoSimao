#pragma once
#include "Obstaculo.h"

class Plataforma : public Obstaculo
{
private:

public:
	Plataforma(Vector2f pos = (Vector2f(0.f, 0.f)));
	~Plataforma();
	void executar();
	void obstacular(Personagem* p = NULL, int d = 0);

	std::string getTipo() const { return "Plataforma"; }

};
