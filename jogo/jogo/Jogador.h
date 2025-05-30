#pragma once
#include "Personagem.h" 
class Jogador: public Personagem
{
private:
	static bool jogador1;
	bool j1;
public:
	Jogador(Vector2f pos = (Vector2f(0.f, 0.f)));
	~Jogador();
	void mover();

	void executar();
	
};

