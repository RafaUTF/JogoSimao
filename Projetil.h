#pragma once
//#include "Personagem.h"
#include "ListaEntidades.h"

namespace Entidades {
	namespace Personagens {
		class Jogador;
		class Personagem;
	}
}

namespace Entidades {
	class Projetil : public Entidade
	{
	protected:
		bool ativo;
		Listas::ListaEntidades* lista;
		unsigned long long duracao;

		Entidades::Personagens::Jogador* pDono;
	public:
		Projetil(Vector2f pos = (Vector2f(0.f, 0.f)), bool dir = true, float raio = 0.f, Listas::ListaEntidades* pl = NULL,
			Entidades::Personagens::Jogador* pdono = nullptr, short int f = 0);
		~Projetil();
		void executar();
		void salvar();

		const bool getAtivo();

		void explodir(Entidades::Personagens::Personagem* pp = nullptr);

		std::string getTipo() const { return "Projetil"; }

		Vector2f getVelocidade();
		void setVelocidade(Vector2f v);
		void setDono(Entidades::Personagens::Jogador* pdono);
	};
}