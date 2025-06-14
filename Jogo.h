#pragma once
#include "Jogador.h"
#include "Chefao.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.h"
#include "Gerenciador_Colisoes.h"
#include "ListaEntidades.h"
#include "Plataforma.h"
#include "Ente.h"
#include "Menu.h"
#include "Fase1.h"
#include "Fase2.h"

class Jogo {
private:
	Fase1* pF1;
	Fase2* pF2;

	//Fase* pFase;

	Gerenciador_Grafico* GG;
	Gerenciador_Colisoes* GC;

	int fase;
	int numPlayers;

public:
	Jogo(int numPlayers_, int fase_);
	~Jogo();
	void executar();
	//void //executar as fases();
};