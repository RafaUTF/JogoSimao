#pragma once

#include <iostream>
using namespace std;
#include <vector>
#include <list>
#include <set>

#include "Jogador.h"
#include "Inimigo.h"
#include "Projetil.h"
#include "Obstaculo.h"
#include "Espinho.h"

class Gerenciador_Colisoes {//chamar todas essas funcoes no executar();

private:
	bool chao1;
	bool chao2;


	vector<Inimigo*> LIs;
	list<Obstaculo*> LOs;
	set<Projetil*> LPs;

	vector<Jogador*> LJs;

	Gerenciador_Colisoes();//privada

	const int verificarDirecao(Entidade* pe1 = NULL, Entidade* pe2 = NULL) const;

	void tratarColisoesJogs();
	void tratarColisoesJogsObstacs();
	void tratarColisoesJogsInimgs();
	void tratarColisoesJogsProjeteis();

	void tratarColisoesInimgsObstacs();
	void tratarColisoesInimgsProjeteis();
	void tratarColisoesProjeteisObstacs();
public:
	static Gerenciador_Colisoes* getInstancia();
	~Gerenciador_Colisoes();
	void executar();
	void retirarProjeteis();
	void retirarPersonagens();

	void incluirInimigo(Inimigo* pi = NULL);
	void incluirObstaculo(Obstaculo* po = NULL);
	void incluirProjetil(Projetil* pj = NULL);
	void incluirJogador(Jogador* pjog = NULL);

	void removerEntidade(Entidade* pE);

	set<Projetil*>& getProjeteis();

	void limpaLista();
};


