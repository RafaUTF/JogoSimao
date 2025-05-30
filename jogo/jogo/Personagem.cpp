#include "Personagem.h"

Personagem::Personagem(Vector2f pos): Entidade(pos), num_vidas(10), agilidade(5.f), vel(Vector2f(0.f,0.f)) {

}


Personagem::~Personagem()
{
}

void Personagem::mover()
{
}


