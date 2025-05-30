#pragma once
#include "Jogador.h"
#include "Inimigo.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gerenciador_Grafico.h"
#include "Gerenciador_Colisoes.h"
#include "ListaEntidades.h"
#include "Plataforma.h"
#include "Ente.h"

class Jogo {
private:
	//Fase1* pF1;
	//Fase2* pF2;
	Jogador* pJog1;
	Jogador* pJog2;
	Inimigo* pInim;
	Plataforma* pPlat;

	ListaEntidades lista;

	Gerenciador_Grafico* GG;
	Gerenciador_Colisoes* GC;
public:
	Jogo();
	~Jogo();
	void executar();
	//void //executar as fases();
};