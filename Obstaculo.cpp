#include "Obstaculo.h"

Obstaculo::Obstaculo(Vector2f pos) :
	danoso(false), Entidade(pos)
{
}

Obstaculo::~Obstaculo()
{
}

bool Obstaculo::isDanoso() const { return danoso;}