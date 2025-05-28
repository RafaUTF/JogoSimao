#pragma once
#include "Ente.h"
class Entidade: public Ente
{
protected:
	float x;
	float y;
public:
	Entidade():x(10.f),y(10.f){}
	~Entidade(){}
};

