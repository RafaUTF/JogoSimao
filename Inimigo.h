#pragma once
#include "Personagem.h"

#include "Jogador.h"


namespace Entidades {
	namespace Personagens {

		class Inimigo : public Personagem
		{
		protected:
			int nivel_maldade;
			bool chefao;
			Jogador* p1;
			Jogador* p2;
			Jogador* pAlvo;
		public:
			Inimigo(Listas::ListaEntidades* t = nullptr, Vector2f pos = (Vector2f(100.f, 100.f)));
			~Inimigo();
			virtual void mover() = 0;

			virtual void executar();
			//virtual void salvar();
			virtual void danificar(Jogador* p = NULL, int d = 0);

			void escolherAlvo();

			void perseguir();

			void colidirInim(Inimigo* p = nullptr, int d = 0);

			void zerarPulo();

			virtual void salvar(json& j)=0;
		};

	}
}