#include "Gerenciador_Colisoes.h"

Gerenciador_Colisoes::Gerenciador_Colisoes()
{
}
Gerenciador_Colisoes::~Gerenciador_Colisoes()
{
}

const bool Gerenciador_Colisoes::verificarColisao(Entidade* pe1, Entidade* pe2) const
{
	if (pe1 == NULL) {
		cout << "pe1 nulo" << endl;
		return false;
	}
	if (pe2 == NULL){
		cout << "pe2 nulo" << endl;
		return false;
	}
	
	
	float a = pe1->getcm().x;
	float b = pe2->getcm().x;
	float dx;
	b > a ? dx = b - a : dx = a - b;
	a = pe1->getcm().y;
	b = pe2->getcm().y;
	float dy;
	b > a ? dy = b - a : dy = a - b;

	if(dx< pe1->getRaio().x+ pe2->getRaio().x
		&& dy< pe1->getRaio().y + pe2->getRaio().y){
		return true;
	}
	return false;

	//if verificar colisao
	//obstaculo->obstacular
}
