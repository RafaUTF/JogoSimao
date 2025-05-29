#pragma once

#include "Jogador.h"
#include "Inimigo.h"

class Gerenciador_Colisoes {//chamar todas essas funcoes no executar();
	
private:
	//vector<*Inimigo> LIs;
	//list<*Obstaculo> LOs;
	//set<*Projetil> LPs;
	Jogador pJog1;
public:
	Gerenciador_Colisoes();
	~Gerenciador_Colisoes();
	const bool verificarColisao(Entidade* pe1, Entidade* pe2) const;
private:
	//void tratarColisoesJogsObstacs();
	//void tratarColisoesJogsInimgs();
	//void tratarColisoesJogsProjeteis();
	//void incluirInimigo(*Inimigo pi);
	//void incluirObstcaulo(*Obstaculo po);
	//void incluirProjetil(*Projetil pj);
	//void executar();
};



