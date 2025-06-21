#pragma once
#include "Obstaculo.h"

namespace Entidades {
	namespace Obstaculos {

		class Plataforma : public Obstaculo
		{
		private:

			float deslocamento; // Deslocamento da plataformaf

		public:
			Plataforma(Vector2f pos = (Vector2f(0.f, 0.f)), float desloc = 0);
			~Plataforma();
			void executar();
			void obstacular(Personagens::Personagem* p = NULL, int d = 0);

			std::string getTipo() const { return "Plataforma"; }

			float getDeslocamento() const { return deslocamento; }

		};
	}
}