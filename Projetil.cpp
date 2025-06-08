#include "Projetil.h"


Projetil::Projetil(Vector2f pos, bool dir, float raio, ListaEntidades* lp):
	Entidade(pos), ativo(true),lista(lp)
{
    if (dir) {
		vel = (Vector2f(10.f, 0));
        corpo.move(raio, 0.f);
    }
    else {
		vel = (Vector2f(-10.f, 0));
        corpo.move(-raio, 0.f);
    }

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
    cout << "DESTRUTORA PROJETIL" << endl;
}

void Projetil::executar()
{
	corpo.move(vel);
}

void Projetil::salvar()
{
}

void Projetil::explodir(Entidade* pe)
{
    lista->retirar(this);
    //retirar do set
}


