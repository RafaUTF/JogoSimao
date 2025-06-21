#pragma once
#include "Inimigo.h"

namespace Entidades {

	namespace Personagens {

		class Chefao : public Inimigo
		{
		private:
			short int forca;

		public:
			Chefao(Listas::ListaEntidades* t = nullptr, Jogador* pp1 = nullptr, Jogador* pp2 = nullptr, Vector2f pos = (Vector2f(100.f, 100.f)));
			Chefao(Listas::ListaEntidades* t, Jogador* pp1, Jogador* pp2,
				Vector2f pos,short int f,int vida);
			~Chefao();
			void executar();
			void salvar();
			void mover();

			std::string getTipo() const { return "Chefao"; }

			void atirar();

			const short int getForca() const { return forca; }
		};

	}
}