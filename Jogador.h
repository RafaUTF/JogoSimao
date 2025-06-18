#pragma once
#include "Personagem.h" 

class Jogador : public Personagem
{
protected:
	int pontos;

	static bool jogador1;
	bool j1;
public:
	Jogador(Vector2f pos = (Vector2f(0.f, 0.f)));
	~Jogador();
	void mover();

	void executar();

	void colidir0(Jogador* p = NULL);

	void atirar();

	std::string getTipo() const { return "Jogador"; }

	const int getPontos() const;

	void operator+=(const int n);
	
	void operator++();
};
