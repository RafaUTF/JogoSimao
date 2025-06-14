#pragma once
#include "Obstaculo.h"
class BandeiraChegada : public Obstaculo
{
	private:
		bool terminoufase;

	public:
		BandeiraChegada(Vector2f pos = (Vector2f(0.f, 0.f)));
		~BandeiraChegada();
		void executar();
		void obstacular(Jogador* p = NULL);
		void causarDano(Jogador* pJog);
};

