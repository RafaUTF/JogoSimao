#pragma once
#include "Inimigo.h"

namespace Entidades {
	namespace Personagens {

		class InimigoPequeno : public Inimigo
		{
		private:
			Vector2f posinicial;
			int direcao;

			float aceleracaoextra;

		public:
			InimigoPequeno(Vector2f pos = (Vector2f(100.f, 100.f)), float acelex = 0);
			~InimigoPequeno();
			void executar();
			void salvar();
			Vector2f getPosicaoInicial();
			Vector2f getPosicaoAtual();
			void mover();

			std::string getTipo() const { return "InimigoPequeno"; }

			float getAceleracaoExtra() const { return aceleracaoextra; }

			void salvar(json& j);
		};

	}
}