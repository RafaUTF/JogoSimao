#pragma once
#include "Ente.h"
class Entidade: public Ente
{
protected:
	//Vector2f posicao;
	// 
	//float x;
	//float y;
public:
	//Entidade(float xx = 20, float yy = 20);
	Entidade(Vector2f pos = (Vector2f(0.f, 0.f)));
	virtual ~Entidade();

	Vector2f getcm();
	//float getXcm();
	//float getYcm();
	Vector2f getRaio();
	//float getRaioX();
	//float getRaioY();
	
	virtual void executar()=0;

};

