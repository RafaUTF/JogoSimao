#pragma once
#include "Entidade.h"

class Personagem: public Entidade
{
protected:
	int num_vidas;
	float agilidade;
	Vector2f vel;
	//float vy;
	//float vx;

public:
	Personagem(Vector2f pos = (Vector2f(0.f, 0.f)));
	~Personagem();
	virtual void mover();
	
	virtual void executar() = 0;

	//float getXcm();
	//float getYcm();

};

