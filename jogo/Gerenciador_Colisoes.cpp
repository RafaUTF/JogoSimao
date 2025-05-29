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
	//if (pe1->getXcm()+pe1->getRaioX() > pe2->getXcm() - pe2->getRaioX()
		//&& pe1->getXcm()< pe2->getXcm()){

	float a = pe1->getXcm();
	float b = pe2->getXcm();
	float dx;
	b > a ? dx = b - a : dx = a - b;
	a = pe1->getYcm();
	b = pe2->getYcm();
	float dy;
	b > a ? dy = b - a : dy = a - b;

	if(dx< pe1->getRaioX()+ pe2->getRaioX()
		&& dy< pe1->getRaioY() + pe2->getRaioY()){
		return true;
	}
	return false;
}
