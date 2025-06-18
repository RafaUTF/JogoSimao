#pragma once
//#include "Personagem.h"
#include "ListaEntidades.h"
class Jogador;
class Personagem;
class Projetil : public Entidade
{
protected:
	bool ativo;
	ListaEntidades* lista;
	unsigned long long duracao;

	Jogador* pDono;
public:
	Projetil(Vector2f pos = (Vector2f(0.f, 0.f)), bool dir = true, float raio = 0.f, ListaEntidades* pl = NULL,
		Jogador* pdono = nullptr, short int f=0);
	~Projetil();
	void executar();
	void salvar();

	const bool getAtivo();

	void explodir(Personagem* pp = nullptr);

	std::string getTipo() const { return "Projetil"; }
};