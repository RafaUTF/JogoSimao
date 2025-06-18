#pragma once
#include "Entidade.h"
#include "ListaEntidades.h"
#include "Projetil.h"

class Personagem : public Entidade
{
protected:
	int num_vidas;
	float agilidade;

	ListaEntidades* tiros;

	int recarga;

	bool comChao;

	bool olhandoDir;



public:
	Personagem(Vector2f pos = (Vector2f(0.f, 0.f)));
	~Personagem();
	virtual void mover();

	virtual void executar() = 0;

	void setChao(bool b);

	virtual void atirar(short int f=1);

	ListaEntidades* getTiros();

	void criarTiros();

	void reduzVelocidade(float fator);
	void restaurarVelocidade();

	virtual void sofrerGravidade();

	void operator--();

	const int getVidas();
	void setVida(int v);

	void colidir(Entidade* pe = NULL, int d = 0);


};