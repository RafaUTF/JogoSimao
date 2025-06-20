#pragma once
#include "Inimigo.h"

namespace Entidades {

	namespace Personagens {

		class Chefao : public Inimigo
		{
		private:
			short int forca;


		public:
			Chefao(Listas::ListaEntidades* t = nullptr, Jogador* pp1 = NULL, Jogador* pp2 = NULL, Vector2f pos = (Vector2f(100.f, 100.f)));
			~Chefao();
			void executar();
			void salvar();
			void mover();

			std::string getTipo() const { return "Chefao"; }


		};

	}
}