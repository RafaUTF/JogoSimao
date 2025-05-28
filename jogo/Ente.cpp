#include "Ente.h"
int Ente::cont(0);
Gerenciador_Grafico* Ente::pGG(0);

Ente::Ente():id(cont++){}

Ente::~Ente()
{

}

void Ente::setpGG(Gerenciador_Grafico* p)
{
	pGG = p;
}

void Ente::desenhar()
{

}
