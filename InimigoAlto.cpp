#include "InimigoAlto.h"

InimigoAlto::InimigoAlto(Vector2f pos) :
	Inimigo(pos)
{
	num_vidas = VIDA_BAIXO;

	nivel_maldade = DANO_ALTO;
	agilidade = 1.f;
	direcao = 1;

	posinicial = pos;


	if (!textura.loadFromFile("inimigoalto.png")) {
		std::cerr << "Erro ao carregar textura: inimigoalto.png" << std::endl;
		corpo.setFillColor(sf::Color::Red); // DEBUG VISUAL
	}

	else {
		corpo.setTexture(&textura);
	}
	cout << "INIMIGOALTO CRIADO" << endl;
	corpo.setSize(Vector2f(64.f, 160.f));
	centralizarEntidade();
}
InimigoAlto::~InimigoAlto()
{
	cout << "destrutora InimigoAlto" << endl;
}

void InimigoAlto::executar()
{
	mover();

}

void InimigoAlto::mover()
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

void InimigoAlto::salvar()
{
}

Vector2f InimigoAlto::getPosicaoInicial()
{
	return posinicial;
}

Vector2f InimigoAlto::getPosicaoAtual()
{
	return corpo.getPosition();
}