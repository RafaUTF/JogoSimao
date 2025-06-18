#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;

using std::cout;
using std::cin;
using std::endl;

#define FPS 60

#define CHAO 640.f
#define DIREITA 960.f
#define TAMANHOTOTALLATERAL 3200.f

#define ESQUERDA 50.f

#define PULO 10
#define ATRITO 0.5f
#define VISCOSO 0.1f
#define GRAVIDADE 0.5f
#define MAX_VEL 10.f//velocidade maxima

#define TEMPO_RECARGA 30

#define TEMPO_PROJETIL 60

#define VISAO_INIMIGO2 80000.f//distancia que o inimigo enxerga ao quadrado

#define CHAO_CHEFE 585.f

#define	NIVEL_MALDADE_BASICO 1
#define	DANO_CHEFE 3
#define	DANO_ALTO 2
#define	DANO_BAIXO 1

#define	ELASTICIDADE_INIMIGO 20.f//usado no danificar do inimigo

#define VIDA_BASE 1
#define VIDA_JOGADOR 10
#define VIDA_CHEFE 50
#define VIDA_ALTO 4
#define VIDA_BAIXO 12

#define	ELASTICIDADE_ESPINHO 10.f