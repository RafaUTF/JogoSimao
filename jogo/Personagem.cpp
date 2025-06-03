#include "Personagem.h"

Personagem::Personagem(Vector2f pos) : Entidade(pos), num_vidas(10),
agilidade(5.f), comChao(false), tiros(), 
recarga(TEMPO_RECARGA) ,olhandoDir(true)
{

}


Personagem::~Personagem()
{
}

void Personagem::mover()
{
}

void Personagem::setChao(bool b)
{
	comChao = b;
}

void Personagem::atirar()
{
	
}

ListaEntidades& Personagem::getTiros()
{
	return tiros;
}


