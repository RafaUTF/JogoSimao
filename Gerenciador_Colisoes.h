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

	static Gerenciador_Colisoes* pgc;

	vector<Inimigo*> LIs;
	list<Obstaculo*> LOs;
	set<Projetil*> LPs;
	
	vector<Jogador*> LJs;

	Gerenciador_Colisoes();//privada
public:
	~Gerenciador_Colisoes();
	void executar();
	//const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
	const int verificarDirecao(Entidade* pe1=NULL, Entidade* pe2=NULL) const;
	//const Vector2f verificarDirecao(Entidade* pe1=NULL, Entidade* pe2=NULL) const;

	void tratarColisoesJogs();
	
	void tratarColisoesJogsObstacs();

	static Gerenciador_Colisoes* getInstancia();

private:
	void tratarColisoesJogsInimgs();
	void tratarColisoesJogsProjeteis();
public:
	void incluirInimigo(Inimigo* pi=NULL);
	void incluirObstaculo(Obstaculo* po=NULL);
	void incluirProjetil(Projetil* pj=NULL);
	void incluirJogador(Jogador* pjog = NULL);
};



