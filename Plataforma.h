#pragma once
#include "Obstaculo.h"

class Plataforma : public Obstaculo
{
private:
	
public:
	Plataforma(Vector2f pos = (Vector2f(0.f, 0.f)));
	~Plataforma();
	void executar();
	void obstacular(Jogador* p=NULL);
	void causarDano(Jogador* pJog);

	std::string getTipo() const{ return "Plataforma"; }

};

