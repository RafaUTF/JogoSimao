#include "Gerenciador_Colisoes.h"

Gerenciador_Colisoes* Gerenciador_Colisoes::pgc(NULL);
Gerenciador_Colisoes* Gerenciador_Colisoes::getInstancia()
{
	if (pgc == NULL)
		pgc = new Gerenciador_Colisoes;
	return pgc;
}

Gerenciador_Colisoes::Gerenciador_Colisoes():
	chao1(false),chao2(false),
	LIs(),LOs(),LPs(),LJs()
{
	LIs.clear();
	LOs.clear();
	LPs.clear();

	LJs.clear();

}
Gerenciador_Colisoes::~Gerenciador_Colisoes()
{
	//passar deletando tudo dentro das listas
	LIs.clear();
	LOs.clear();
	LPs.clear();
	LJs.clear();

	delete pgc;
}

void Gerenciador_Colisoes::executar() {
	
	LJs[0]->setChao(false);
	chao1 = false;
	
	if (LJs.size()>1) {
		LJs[1]->setChao(false);
		chao2 = false;
		tratarColisoesJogs();
	}
	
	tratarColisoesJogsProjeteis();
	
	tratarColisoesJogsInimgs();
	tratarColisoesJogsObstacs();
	

	LJs[0]->setChao(chao1);

	if (LJs.size()>1) {
		LJs[1]->setChao(chao2);
	}



	//nao deu certo

	/*
	verificaObsIni();
	verificaIni();
	verificaObs();
	verificaProjetil();
	verificaObsProjetil();
	*/
}
float modulo(float x) {
	return x < 0 ? (-1.f) * x : x;
}

const int Gerenciador_Colisoes::verificarDirecao(Entidade* pe1, Entidade* pe2) const
{
	if (pe1 == NULL) {
		cout << "pe1 nulo" << endl;
		return 0;
	}
	if (pe2 == NULL) {
		cout << "pe2 nulo" << endl;
		return 0;
	}
	float dx = pe2->getcm().x - pe1->getcm().x,//+ -> colisao dir do pe1
		dy = pe2->getcm().y - pe1->getcm().y,//+ -> colisao em baixo do pe1
		drx = pe1->getRaio().x + pe2->getRaio().x,
		dry = pe1->getRaio().y + pe2->getRaio().y;
	if (modulo(dx) < drx && modulo(dy) < dry) {
		if (drx - modulo(dx) < dry - modulo(dy)) {//colisao lado
			if(dx>0)//dir pe1
				return 3;
			else//esq pe1
				return 2;
		}
		else{//colisao vertical
			if (dy > 0)//baixo pe1
				return 4;
			else//cima pe1
				return 1;
		}
	}
	return 0;
}


//empurra
void Gerenciador_Colisoes::tratarColisoesJogs() {

	Jogador* p1 = LJs[0];
	Jogador* p2 = LJs[1];
	int d = verificarDirecao(p1, p2);
	if (d != 0) {
		float dx = p2->getcm().x - p1->getcm().x,//+ -> colisao dir do pe1
			dy = p2->getcm().y - p1->getcm().y,//+ -> colisao em baixo do pe1
			drx = p1->getRaio().x + p2->getRaio().x,
			dry = p1->getRaio().y + p2->getRaio().y,
			x = drx - modulo(dx), y = dry - modulo(dy);

		if (d == 1) {
			chao2 = true;
			p2->getVel().y = p1->getVel().y;
			p1->getCorpo().move(0.f, y/2);
			p2->getCorpo().move(0.f, -y/2);
			/*
			p2->getCorpo().setPosition(
				p2->getcm().x,
				p1->getcm().y - p1->getRaio().y - p2->getRaio().y
			);*/
		}
		if (d == 4) {
			chao1=true;
			p1->getVel().y = p2->getVel().y;
			p1->getCorpo().move(0.f, -y / 2);
			p2->getCorpo().move(0.f, y / 2);
			/*
			p1->getCorpo().setPosition(
				p1->getcm().x,
				p2->getcm().y - p1->getRaio().y - p2->getRaio().y
			);*/
		}

		if (d == 2) {
			p1->getVel().x = 0.f;
			p2->getVel().x = 0.f;
			p1->getCorpo().move(x / 2, 0.f);
			p2->getCorpo().move(-x / 2, 0.f);
			/*
			p1->getCorpo().setPosition(
				p1->getcm().x + p1->getRaio().x + p2->getRaio().x,
				p1->getcm().y
			);*/
		}
		if (d == 3) {
			p1->getVel().x = 0.f;
			p2->getVel().x = 0.f;

			p1->getCorpo().move(-x / 2, 0.f);
			p2->getCorpo().move(x / 2, 0.f);
			/*
			p1->getCorpo().setPosition(
				p2->getcm().x - p1->getRaio().x - p2->getRaio().x,
				p1->getcm().y
			);*/
		}
	}
}


/*
const Vector2f Gerenciador_Colisoes::verificarDirecao(Entidade* pe1, Entidade* pe2) const
{
	if (pe1 == NULL) {
		cout << "pe1 nulo" << endl;
		return Vector2f(0.f, 0.f);
	}
	if (pe2 == NULL) {
		cout << "pe2 nulo" << endl;
		return Vector2f(0.f, 0.f);
	}
	float dx = pe2->getcm().x - pe1->getcm().x,//+ -> colisao dir do pe1
		dy = pe2->getcm().y - pe1->getcm().y,//+ -> colisao em baixo do pe1
		drx = pe1->getRaio().x + pe2->getRaio().x,
		dry = pe1->getRaio().y + pe2->getRaio().y;
	if (modulo(dx) < drx && modulo(dy) < dry) {
		if (modulo(dx) < pe1->getRaio().x) {
			dx = 0.f;
		}
		if (modulo(dy) < pe1->getRaio().y)
			dy = 0.f;
		return Vector2f(-dx, -dy);
	}
	
	return Vector2f(0.f, 0.f);
}
*/
/*
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
}*/

/*
const float Gerenciador_Colisoes::verificarDirecao(Entidade* pe1, Entidade* pe2) const
{
	if (pe1 == NULL) {
		cout << "pe1 nulo" << endl;
		return false;
	}
	if (pe2 == NULL) {
		cout << "pe2 nulo" << endl;
		return false;
	}
	float dx = pe1->getcm().x - pe2->getcm().x,//+ -> colisao esq do pe1
		dy = pe1->getcm().y - pe2->getcm().y,//+ -> colisao em cima do pe1
		drx = pe1->getRaio().x + pe2->getRaio().x,
		dry = pe1->getRaio().y + pe2->getRaio().y;
	if (modulo(dx) < drx && modulo(dy) < dry) {
		if (dx < 0 && dy>0)
			return 3;
	}
	/*
	if (dx > 0) {//possivel colisao esq
		if (dx < drx && modulo(dy) < dry)
			return 2;
	}
	else {//possivel colisao dir
		if (modulo(dx) < drx && modulo(dy) < dry)
			return 3;
	}
	//nao vai cair nunca!
	if (dy > 0) {//possivel colisao cima
		if (dy < dry && modulo(dx) < drx)
			return 1;
	}
	else {//possivel colisao baixo
		if (modulo(dy) < dry && modulo(dy) < dry)
			return 4;
	}
	/*
	if (pe1->getRaio().y + pe2->getRaio().y > modulo(pe2->getcm().y - pe1->getcm().y)) {
		float a = pe2->getcm().x - pe1->getcm().x,
			d = pe1->getRaio().x + pe2->getRaio().x;
		if (a > 0 && d > a)
			return 3;
		if (a<0 && d >a * (-1.f))
			return 2;
	}
	*/

/*
	if (pe1->getRaio().x + pe2->getRaio().x > modulo(pe2->getcm().x - pe1->getcm().x)) {
		//cout << "colisao direita p1" << endl;
		return 3;
	}
	if (pe1->getRaio().x + pe2->getRaio().x > modulo(pe1->getcm().x - pe2->getcm().x)) {
		//cout << "colisao direita p1" << endl;
		return 2;
	}
	*/


void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
	//CHAMAR OBSTACULAR PARA PARAR O JOGADOR

	Obstaculo* po = NULL;
	Jogador* pJog1 = NULL;
	int d = 0;
	for (int i = 0;i < LJs.size();i++) {
		pJog1 = LJs[i];
		for (list<Obstaculo*>::iterator it = LOs.begin();it != LOs.end();it++) {
			po = *it;
			d = verificarDirecao(pJog1, po);
			if (d != 0) {
				if (d == 1) {
					pJog1->getVel().y = 0.f;
					pJog1->getCorpo().setPosition(
						pJog1->getcm().x,
						po->getcm().y + pJog1->getRaio().y + po->getRaio().y
					);
				}
				if (d == 4) {
					pJog1->getVel().y = 0.f;
					i == 0 ? chao1 = true : chao2 = true;
					pJog1->getCorpo().setPosition(
						pJog1->getcm().x,
						po->getcm().y - pJog1->getRaio().y - po->getRaio().y
					);
				}
				if (d == 2) {
					pJog1->getVel().x = 0.f;
					pJog1->getCorpo().setPosition(
						po->getcm().x + pJog1->getRaio().x + po->getRaio().x,
						pJog1->getcm().y
					);
				}
				if (d == 3) {
					pJog1->getVel().x = 0.f;
					pJog1->getCorpo().setPosition(
						po->getcm().x - pJog1->getRaio().x - po->getRaio().x,
						pJog1->getcm().y
					);
				}
				
			}
		}

	}
	
}


/*
void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
	//CHAMAR OBSTACULAR PARA PARAR O JOGADOR
	Obstaculo* po = NULL;
	Jogador* pJog1 = LJs[0];
	Jogador* pJog2 = LJs[1];
	for (list<Obstaculo*>::iterator it = LOs.begin();it != LOs.end();it++) {
		po = *it;
		int d = verificarDirecao(pJog1, po);
		if (d != 0) {
			if (d == 1) {
				pJog1->getVel().y = 0.f;
				pJog1->getCorpo().setPosition(
					pJog1->getcm().x,
					po->getcm().y + pJog1->getRaio().y + po->getRaio().y
				);
			}
			if (d == 4) {
				pJog1->getVel().y = 0.f;
				chao1 = true;
				pJog1->getCorpo().setPosition(
					pJog1->getcm().x,
					po->getcm().y - pJog1->getRaio().y - po->getRaio().y
				);
			}
			if (d == 2) {
				pJog1->getVel().x = 0.f;
				pJog1->getCorpo().setPosition(
					po->getcm().x + pJog1->getRaio().x + po->getRaio().x,
					pJog1->getcm().y
				);
			}
			if (d == 3) {
				pJog1->getVel().x = 0.f;
				pJog1->getCorpo().setPosition(
					po->getcm().x - pJog1->getRaio().x - po->getRaio().x,
					pJog1->getcm().y
				);
			}

		}
	
		d = verificarDirecao(pJog2, po);
		if (d != 0) {
			if (d == 1) {
				pJog2->getVel().y = 0.f;
				pJog2->getCorpo().setPosition(
					pJog2->getcm().x,
					po->getcm().y + pJog2->getRaio().y + po->getRaio().y
				);
			}
			if (d == 4) {
				pJog2->getVel().y = 0.f;
				chao2 = true;
				pJog2->getCorpo().setPosition(
					pJog2->getcm().x,
					po->getcm().y - pJog2->getRaio().y - po->getRaio().y
				);
			}
			if (d == 2) {
				pJog2->getVel().x = 0.f;
				pJog2->getCorpo().setPosition(
					po->getcm().x + pJog2->getRaio().x + po->getRaio().x,
					pJog2->getcm().y
				);
			}
			if (d == 3) {
				pJog2->getVel().x = 0.f;
				pJog2->getCorpo().setPosition(
					po->getcm().x - pJog2->getRaio().x - po->getRaio().x,
					pJog2->getcm().y
				);
			}

		}
		
	}
}
*/
/*
void Gerenciador_Colisoes::tratarColisoesJogs()
{

	Jogador* pJog1 = LJs[0];
	Jogador* pJog2 = LJs[1];
	int d = verificarDirecao(pJog1, pJog2);

	//pJog2->setDir(verificarDirecao(pJog2, pJog1));
	if (d != 0) {
		if (d == 1) {
			pJog2->setChao(true);
			pJog2->getCorpo().setPosition(
				pJog2->getcm().x,
				pJog1->getcm().y - pJog1->getRaio().y - pJog2->getRaio().y
			);
		}
		if (d == 4) {
			pJog1->setChao(true);
			pJog1->getCorpo().setPosition(
				pJog1->getcm().x,
				pJog2->getcm().y - pJog1->getRaio().y - pJog2->getRaio().y
			);
		}
		if (d == 2) {
			pJog1->getCorpo().setPosition(
				pJog2->getcm().x + pJog1->getRaio().x + pJog2->getRaio().x,
				pJog1->getcm().y
			);
		}
		if (d == 3) {
			pJog1->getCorpo().setPosition(
				pJog2->getcm().x - pJog1->getRaio().x - pJog2->getRaio().x,
				pJog1->getcm().y
			);
		}

	}
	if (pJog1->getDir() != d) {
		pJog1->setDir(d);
		// pJog2->setChao(false);
		pJog1->setChao(false);
	}

	//JOGADOR 2

	d = verificarDirecao(pJog2, pJog1);//ALTERAR

	//pJog2->setDir(verificarDirecao(pJog2, pJog1));
	if (d != 0) {
		if (d == 1) {
			//pJog1->setChao(true);
			//pJog1->getCorpo().setPosition(
			//	pJog1->getcm().x,
			//	pJog2->getcm().y - pJog1->getRaio().y - pJog2->getRaio().y
			//);
		}
		if (d == 4) {
			pJog2->setChao(true);
			pJog2->getCorpo().setPosition(
				pJog2->getcm().x,
				pJog1->getcm().y - pJog1->getRaio().y - pJog2->getRaio().y
			);
		}
		if (d == 2) {
			pJog2->getCorpo().setPosition(
				pJog1->getcm().x + pJog1->getRaio().x + pJog2->getRaio().x,
				pJog2->getcm().y
			);
		}
		if (d == 3) {
			pJog2->getCorpo().setPosition(
				pJog1->getcm().x - pJog1->getRaio().x - pJog2->getRaio().x,
				pJog2->getcm().y
			);
		}

	}
	if (pJog2->getDir() != d) {
		pJog2->setDir(d);
		pJog2->setChao(false);
		//pJog1->setChao(false);
	}

}
*/

void Gerenciador_Colisoes::tratarColisoesJogsInimgs() {
	Inimigo* pi = NULL;
	Jogador* pJog1 = NULL;
	int d = 0;
	for (int i = 0;i < LJs.size();i++) {
		pJog1 = LJs[i];
		for (vector<Inimigo*>::iterator it = LIs.begin();it != LIs.end();it++) {
			pi = *it;
			d = verificarDirecao(pJog1, pi);
			if (d != 0) {
				pi->danificar(pJog1);
				if (d == 1) {
					pJog1->getVel().y = 0.f;
					pJog1->getCorpo().setPosition(
						pJog1->getcm().x,
						pi->getcm().y + pJog1->getRaio().y + pi->getRaio().y
					);
				}
				if (d == 4) {
					pJog1->getVel().y = 0.f;
					i == 0 ? chao1 = true : chao2 = true;
					pJog1->getCorpo().setPosition(
						pJog1->getcm().x,
						pi->getcm().y - pJog1->getRaio().y - pi->getRaio().y
					);
				}
				if (d == 2) {
					pJog1->getVel().x = 0.f;
					pJog1->getCorpo().setPosition(
						pi->getcm().x + pJog1->getRaio().x + pi->getRaio().x,
						pJog1->getcm().y
					);
				}
				if (d == 3) {
					pJog1->getVel().x = 0.f;
					pJog1->getCorpo().setPosition(
						pi->getcm().x - pJog1->getRaio().x - pi->getRaio().x,
						pJog1->getcm().y
					);
				}

			}
		}
	
	}
}




void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {//DESATUALIZADO!
	Projetil* pj = NULL;
	Jogador* pJog1 = NULL;
	int d = 0;
	for (int i = 0;i < LJs.size();i++) {
		pJog1 = LJs[i];
		for (set<Projetil*>::iterator it = LPs.begin();it != LPs.end();it++) {
			pj = *it;
			d = verificarDirecao(pJog1, pj);
			if (d != 0) {
				if (d == 1) {
					pJog1->getVel().y = 0.f;
					pJog1->getCorpo().setPosition(
						pJog1->getcm().x,
						pj->getcm().y + pJog1->getRaio().y + pj->getRaio().y
					);
				}
				if (d == 4) {
					pJog1->getVel().y = 0.f;
					i == 0 ? chao1 = true : chao2 = true;
					pJog1->getCorpo().setPosition(
						pJog1->getcm().x,
						pj->getcm().y - pJog1->getRaio().y - pj->getRaio().y
					);
				}
				if (d == 2) {
					pJog1->getVel().x = 0.f;
					pJog1->getCorpo().setPosition(
						pj->getcm().x + pJog1->getRaio().x + pj->getRaio().x,
						pJog1->getcm().y
					);
				}
				if (d == 3) {
					pJog1->getVel().x = 0.f;
					pJog1->getCorpo().setPosition(
						pj->getcm().x - pJog1->getRaio().x - pj->getRaio().x,
						pJog1->getcm().y
					);
				}

			}
		}

	}
}

void Gerenciador_Colisoes::incluirInimigo(Inimigo* pi) {
	if (pi)
		LIs.push_back(pi);
	else
		cout << "ponteiro inimigo nulo nao incluido no vector" << endl;
}

void Gerenciador_Colisoes::incluirObstaculo(Obstaculo* po) {
	if (po)
		LOs.push_back(po);
	else
		cout << "ponteiro obstaculo nulo nao incluido no list" << endl;
}

void Gerenciador_Colisoes::incluirProjetil(Projetil* pj) {
	if (pj)
		LPs.insert(pj);
	else
		cout << "ponteiro projetil nulo nao incluido no set" << endl;
}

void Gerenciador_Colisoes::incluirJogador(Jogador* pjog)
{
	if (pjog)
		LJs.push_back(pjog);
	else
		cout << "ponteiro jogador nulo nao incluido no vector" << endl;
}

