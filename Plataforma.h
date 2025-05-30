#pragma once
#include "Entidade.h"

class Plataforma : public Entidade
{
private:
	float tam_x;
	float tam_y;

public:
	Plataforma();
	~Plataforma();
};

