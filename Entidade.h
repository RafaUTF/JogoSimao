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
		//Entidade(float xx = 20, float yy = 20);
		Entidade(Vector2f pos = (Vector2f(0.f, 0.f)));
		virtual ~Entidade();

		Vector2f getcm();
		//float getXcm();
		//float getYcm();
		Vector2f getRaio();
		//float getRaioX();
		//float getRaioY();

		void centralizarEntidade();

		virtual void executar() = 0;

		void setDir(int v = 0);
		int getDir();

		void setVel(Vector2f v = (Vector2f(0.f, 0.f)));

		Vector2f& getVel();

		virtual const int getVidas();

		virtual std::string getTipo() const = 0;
	};
}