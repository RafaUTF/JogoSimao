#pragma once
#include "Entidade.h"

class Personagem: public Entidade
{
protected:
	int num_vidas;
	float agilidade;
	float vy;
	float vx;
	float vg;
public:
	Personagem();
	~Personagem();
	virtual void mover();
	
	//float getXcm();
	//float getYcm();

};

