#pragma once
#include "Personagem.h" 
class Jogador: public Personagem
{
private:
	static bool jogador1;
	bool j1;
public:
	Jogador();
	~Jogador();
	void mover();

	void executar();
	
};

