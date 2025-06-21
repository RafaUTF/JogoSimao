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
#define FINALFASE 3100.f

#define ESQUERDA 50.f

#define ATRITO 0.5f
#define VISCOSO 0.1f
#define GRAVIDADE 0.5f
#define MAX_VEL 5.f//velocidade maxima

#define TEMPO_RECARGA 30

#define TEMPO_PROJETIL 60

#define VISAO_INIMIGO2 80000.f//distancia que o inimigo enxerga ao quadrado

//DANO FISICO INIMIGOS
#define	NIVEL_MALDADE_BASICO 1
#define	DANO_CHEFE 5
#define	DANO_ALTO 3
#define	DANO_BAIXO 2

//VIDAS
#define VIDA_BASE 1
#define VIDA_JOGADOR 12
#define VIDA_CHEFE 5
#define VIDA_ALTO 3
#define VIDA_BAIXO 2

//ELASTICIDADES
#define	ELASTICIDADE_INIMIGO 20.f//usado no danificar do inimigo
#define	ELASTICIDADE_ESPINHO 10.f

//VELOCIDADE PROJETEIS
#define  VY0 -3.f

#define MAX_FORCA_CHEFE 15
#define MIN_FORCA_CHEFE 5
#define FORCA_JOG 10


#define CHAO_CHEFE 785.f

#define MAX_CHEFES 5

//ACELERACAO PERSONAGENS
#define ACELERACAO_BASE 5.f
#define ACELERACAO_CHEFE 0.2f
#define ACELERACAO_JOG 0.8f
#define ACELERACAO_ALTO 1.f
#define ACELERACAO_BAIXO 2.f

//PULO
#define PULO_JOG -18.f
#define PULO_INIMIGO -12.f
#define PULO_FRACO -10.f

#define TAM_PROJ_CHEFE 50.f
#define TAM_PROJ_JOG 20.f