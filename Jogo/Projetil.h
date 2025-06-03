#pragma once
#include "Entidade.h"

class Projetil: public Entidade
{
protected:
	bool ativo;
public:
	Projetil(Vector2f pos = (Vector2f(0.f, 0.f)),bool dir=true);
	~Projetil();
	void executar();
	void salvar();
};

