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
#include "Fase1.h"
#include "Fase2.h"

class Jogo {
private:
	Fases::Fase1* pF1;
	Fases::Fase2* pF2;

	Gerenciadores::Gerenciador_Grafico* GG;
	Gerenciadores::Gerenciador_Colisoes* GC;

	int fase;
	int numPlayers;

public:
	Jogo();
	~Jogo();
	void executarFase();
	void executar();
	Fases::Fase* getFase();
	void mudarParaFase2(const std::string& caminho);
};