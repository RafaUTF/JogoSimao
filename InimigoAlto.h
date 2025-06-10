#pragma once
#include "Inimigo.h"

class InimigoAlto : public Inimigo
{
	private:
		Vector2f posinicial;
		int direcao;
	public:
		InimigoAlto(Vector2f pos = (Vector2f(100.f, 100.f)));
		~InimigoAlto();
		void executar();
		void salvar();
		Vector2f getPosicaoInicial();
		Vector2f getPosicaoAtual();
		void mover();
};

