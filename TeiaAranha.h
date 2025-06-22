#pragma once
#include "Obstaculo.h"
#include "Jogador.h"

namespace Entidades {
	namespace Obstaculos {

		class TeiaAranha : public Obstaculo
		{
		private:
			float reducao;

		public:
			TeiaAranha(Vector2f pos = (Vector2f(0.f, 0.f)), float redux = 0);
			~TeiaAranha();
			void obstacular(Personagens::Personagem* p = NULL, int d = 0);
			void executar();

			std::string getTipo() const { return "TeiaAranha"; }

			float getReducao() const { return reducao; }

			void salvar(json& j);
		};
	}
}