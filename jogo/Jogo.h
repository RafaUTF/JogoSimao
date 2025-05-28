#pragma once
#include "Jogador.h"
#include "Inimigo.h"
//#include "Gerenciador_Grafico.h"
#include <iostream>
#include <SFML/Graphics.hpp>


class Jogo {
private:
	//Fase1* pF1;
	//Fase2* pF2;
	Jogador* pJog1;
	Jogador* pJog2;
	Inimigo* pInim;
	//Gerenciador_Grafico* GG;
public:
	Jogo();
	~Jogo();
	void executar();
	//void //executar as fases();
};