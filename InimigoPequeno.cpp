#include "InimigoPequeno.h"

InimigoPequeno::InimigoPequeno(Vector2f pos) :
	Inimigo(pos)
{
	agilidade = 1.f;
	direcao = 1;

	posinicial = pos;


	if (!textura.loadFromFile("inimigopequeno.png")) {
		std::cerr << "Erro ao carregar a textura INIMIGOPEQUENO" << std::endl;
	}
	else {
		corpo.setTexture(&textura);
	}
	cout << "INIMIGOPEQUENO CRIADO" << endl;
	corpo.setSize(Vector2f(64.f, 64.f));
	centralizarEntidade();
}
InimigoPequeno::~InimigoPequeno()
{
}

void InimigoPequeno::executar()
{
	mover();

}

void InimigoPequeno::mover()
{
	
	Vector2f posAtual = corpo.getPosition();
	float distancia = posAtual.x - posinicial.x;

	if (direcao == 1 && distancia >= 96.f) {
		direcao = -1;
	}
	else if (direcao == -1 && distancia <= 0.f) {
		direcao = 1;
	}

	corpo.setPosition(posAtual.x + agilidade * direcao, posAtual.y);
}

void InimigoPequeno::salvar()
{
}

Vector2f InimigoPequeno::getPosicaoInicial()
{
	return posinicial;
}

Vector2f InimigoPequeno::getPosicaoAtual()
{
	return corpo.getPosition();
}
