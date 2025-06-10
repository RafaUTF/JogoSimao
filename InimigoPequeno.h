#pragma once
#include "Inimigo.h"
class InimigoPequeno : public Inimigo
{
private:
	Vector2f posinicial;
	int direcao;
public:
	InimigoPequeno(Vector2f pos = (Vector2f(100.f, 100.f)));
	~InimigoPequeno();
	void executar();
	void salvar();
	Vector2f getPosicaoInicial();
	Vector2f getPosicaoAtual();
	void mover();
};

