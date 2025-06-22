#pragma once
#include "Ente.h"

namespace Entidades {

	class Entidade : public Ente
	{
	protected:
		float massa;
		Vector2f vel;

		int dirColisao;

	public:
		
		Entidade(Vector2f pos);
		Entidade();

		virtual ~Entidade();

		Vector2f getcm();
		
		Vector2f getRaio();
		

		void centralizarEntidade();

		virtual void executar() = 0;

		void setDir(int v = 0);
		int getDir();

		void setVel(Vector2f v = (Vector2f(0.f, 0.f)));

		Vector2f& getVel();

		virtual const int getVidas();

		virtual std::string getTipo() const = 0;

		virtual void salvar(json& j) = 0;

		void salvarPos(json& j);
	};
}