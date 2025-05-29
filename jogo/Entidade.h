#pragma once
#include "Ente.h"
class Entidade: public Ente
{
protected:
	//::RectangleShape corpo;
	float x;
	float y;
public:
	Entidade();
	virtual ~Entidade();
	float getXcm();
	float getYcm();
	float getRaioX();
	float getRaioY();
	
	virtual void executar();

};

