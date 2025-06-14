#pragma once
#include "Personagem.h" 

class Jogador: public Personagem
{
protected:
	static bool jogador1;
	bool j1;
public:
	Jogador(Vector2f pos = (Vector2f(0.f, 0.f)));
	~Jogador();
	void mover();

	void executar();
	
	void colidir(Jogador* p = NULL);

	void atirar();

	


};

