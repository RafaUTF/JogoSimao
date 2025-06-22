#pragma once
#include "Entidade.h"
#include "Jogador.h"
#include <string>
namespace Entidades {
	namespace Obstaculos {

		class Obstaculo : public Entidade
		{
		protected:
			bool danoso;
			// float hitbox? 
		public:
			Obstaculo(Vector2f pos = (Vector2f(0.f, 0.f)));
			~Obstaculo();
			virtual void executar() = 0;
			virtual void obstacular(Personagens::Personagem* p = NULL, int d = 0) = 0;
			bool isDanoso() const;
			virtual void causarDano(Personagens::Personagem* pJog = NULL);

			virtual void salvar(json& j)=0;
		};
	}
}