#pragma once
#include "Inimigo.h"

namespace Entidades {
	namespace Personagens {

		class InimigoAlto : public Inimigo
		{
		private:
			Vector2f posinicial;
			int direcao;

			int distanciapadrao;

		public:
			InimigoAlto(Vector2f pos = (Vector2f(100.f, 100.f)), int distpad = 0);
			~InimigoAlto();
			void executar();
			void salvar();
			Vector2f getPosicaoInicial();
			Vector2f getPosicaoAtual();
			void mover();

			std::string getTipo() const { return "InimigoAlto"; }
			int getDistanciaPadrao() const { return distanciapadrao; }

		};

	}
}