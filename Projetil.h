#pragma once
#include "Entidade.h"
#include "ListaEntidades.h"

class Projetil: public Entidade
{
protected:
	bool ativo;
	ListaEntidades* lista;
public:
	Projetil(Vector2f pos = (Vector2f(0.f, 0.f)), bool dir = true, float raio=0.f,ListaEntidades* pl=NULL);
	~Projetil();
	void executar();
	void salvar();

	void explodir(Entidade* pe = NULL);
};

