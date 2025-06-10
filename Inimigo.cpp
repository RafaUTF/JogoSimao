#include "Inimigo.h"

Inimigo::Inimigo(Vector2f pos) :
    Personagem(pos)
    ,nivel_maldade(0)
{
    agilidade = 1.f;

    corpo.setSize(Vector2f(150.f, 70.f));
    centralizarEntidade();

}

Inimigo::~Inimigo()
{
}

void Inimigo::executar()
{
    mover();
}

void Inimigo::danificar(Jogador* p)
{
    cout << "atacou" << endl;
}
