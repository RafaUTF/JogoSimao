#include "Projetil.h"


Projetil::Projetil(Vector2f pos, bool dir):
	Entidade(pos), ativo(true)
{
	if(dir)
		vel = (Vector2f(10.f, 0));
	else
		vel = (Vector2f(-10.f, 0));

    /*
    if (!textura.loadFromFile("boss.png")) {
        std::cerr << "Erro ao carregar a textura BOSS!" << std::endl;
    }
    else {
        corpo.setTexture(textura);
    }
    */
    corpo.setSize(Vector2f(50.f, 50.f));
    centralizarEntidade();
    corpo.setFillColor(Color::White);
}

Projetil::~Projetil()
{
}

void Projetil::executar()
{
	corpo.move(vel);
}

void Projetil::salvar()
{
}
