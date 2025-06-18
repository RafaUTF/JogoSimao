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
		void obstacular(Personagem* p = NULL,int d=0);
		void causarDano(Jogador* pJog);

		std::string getTipo() const{ return "BandeiraChegada"; }

};

