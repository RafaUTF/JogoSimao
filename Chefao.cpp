#include "Chefao.h"



Chefao::Chefao(Jogador* pp1, Jogador* pp2, Vector2f pos):
	Inimigo(pp1,pp2,pos), forca(100)
{
	agilidade = 0.7f;

	criarTiros();

	corpo.setSize(Vector2f(150.f, 200.f));
	centralizarEntidade();
	corpo.setFillColor(Color::Magenta);
}
Chefao::~Chefao()
{
}

void Chefao::executar()
{
	mover();//mover inimigo
	atirar();
	tiros->percorrer();
}

void Chefao::salvar()
{
}
