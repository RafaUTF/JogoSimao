#pragma once
#include "Entidade.h"

class Obstaculo : public Entidade
{
private:
	bool danoso;
	// float hitbox? 
public:
	Obstaculo(Vector2f pos = (Vector2f(0.f, 0.f)));
	~Obstaculo();
	virtual void executar() = 0;
	virtual void obstacular() = 0;
};

