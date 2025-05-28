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
	Inimigo(Jogador* pp1=NULL, Jogador* pp2=NULL);
	~Inimigo();
	virtual void mover();

};

