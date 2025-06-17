#pragma once
//#include "Personagem.h"
#include "ListaEntidades.h"
class Personagem;
class Projetil : public Entidade
{
protected:
	bool ativo;
	ListaEntidades* lista;

	unsigned long long duracao;
public:
	Projetil(Vector2f pos = (Vector2f(0.f, 0.f)), bool dir = true, float raio = 0.f, ListaEntidades* pl = NULL);
	~Projetil();
	void executar();
	void salvar();

	const bool getAtivo();

	void explodir(Personagem* pp = nullptr);

	std::string getTipo() const { return "Projetil"; }
};
