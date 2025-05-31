#pragma once

#include "Jogador.h"
#include "Inimigo.h"
//#include "Projetil.h"
class Projetil;
#include "Obstaculo.h"
class Gerenciador_Colisoes {//chamar todas essas funcoes no executar();
	
private:
	//vector<*Inimigo> LIs;
	//list<*Obstaculo> LOs;
	//set<*Projetil> LPs;
	Jogador pJog1;
public:
	Gerenciador_Colisoes();
	~Gerenciador_Colisoes();
	void executar();
	const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
private:
	void tratarColisoesJogsObstacs();
	void tratarColisoesJogsInimgs();
	void tratarColisoesJogsProjeteis();
	void incluirInimigo(Inimigo* pi=NULL);
	void incluirObstcaulo(Obstaculo* po=NULL);
	void incluirProjetil(Projetil* pj=NULL);
};



