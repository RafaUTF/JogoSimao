#pragma once
#include "Personagem.h"

#include "Jogador.h"

class Inimigo: public Personagem
{
protected:
	int nivel_maldade;
	Jogador* p1;
	Jogador* p2;
public:
	Inimigo(Jogador* pp1=NULL, Jogador* pp2=NULL, Vector2f pos = (Vector2f(100.f, 100.f)));
	~Inimigo();
	virtual void mover();

	virtual void executar();
	//virtual void salvar();
	virtual void danificar(Jogador* p=NULL);
};



