#include "Gerenciador_Colisoes.h"

Gerenciador_Colisoes* Gerenciador_Colisoes::getInstancia()
{
	static Gerenciador_Colisoes instancia;
	return &instancia;
}

void Gerenciador_Colisoes::retirarProjeteis()
{
	set<Projetil*>::iterator it = LPs.begin();
	while (it != LPs.end()) {
		if (*it && (*it)->getAtivo() == false) {
			it = LPs.erase(it);
			cout << "projetil retirado Gerenciador_Colisoes" << endl;
		}
		else
			it++;
	}
}

void Gerenciador_Colisoes::retirarPersonagens()
{
	vector<Inimigo*>::iterator it = LIs.begin();
	while (it != LIs.end()) {
		if (*it && (*it)->getVidas() == 0) {
			it = LIs.erase(it);
			cout << "INIMIGO retirado Gerenciador_Colisoes" << endl;
		}
		else
			it++;
	}

	vector<Jogador*>::iterator it2 = LJs.begin();
	while (it2 != LJs.end()) {
		if (*it2 && (*it2)->getVidas() == 0) {
			it2 = LJs.erase(it2);
			cout << "JOGADOR retirado Gerenciador_Colisoes" << endl;
		}
		else
			it2++;
	}
}

Gerenciador_Colisoes::Gerenciador_Colisoes() :
	chao1(false), chao2(false),
	LIs(), LOs(), LPs(), LJs()
{
	LIs.clear();
	LOs.clear();
	LPs.clear();

	LJs.clear();

	cout << "Gerenciador_Colisoes criado" << endl;
}
Gerenciador_Colisoes::~Gerenciador_Colisoes()
{
	//passar deletando tudo dentro das listas
	LIs.clear();
	LOs.clear();
	LPs.clear();
	LJs.clear();

	cout << "destrutora Gerenciador_Colisoes" << endl;
}

void Gerenciador_Colisoes::executar() {

	LJs[0]->setChao(false);
	chao1 = false;

	if (LJs.size() > 1) {
		LJs[1]->setChao(false);
		chao2 = false;
		tratarColisoesJogs();
	}
	//inimigos
	tratarColisoesInimgsObstacs();
	tratarColisoesInimgsProjeteis();

	tratarColisoesProjeteisObstacs();

	//jogadores
	tratarColisoesJogsProjeteis();
	tratarColisoesJogsInimgs();
	tratarColisoesJogsObstacs();

	LJs[0]->setChao(chao1);

	if (LJs.size() > 1) {
		LJs[1]->setChao(chao2);
	}

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
			if (dx > 0)//dir pe1
				return 3;
			else//esq pe1
				return 2;
		}
		else {//colisao vertical
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
			p1->getCorpo().move(0.f, y / 2);
			p2->getCorpo().move(0.f, -y / 2);
			/*
			p2->getCorpo().setPosition(
				p2->getcm().x,
				p1->getcm().y - p1->getRaio().y - p2->getRaio().y
			);*/
		}
		if (d == 4) {
			chao1 = true;
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

void Gerenciador_Colisoes::tratarColisoesJogsObstacs() {
	//CHAMAR OBSTACULAR PARA PARAR O JOGADOR

	Obstaculo* po = NULL;
	Jogador* pJog1 = NULL;
	int d = 0;
	for (int i = 0;i < LJs.size();i++) {
		pJog1 = LJs[i];
		pJog1->restaurarVelocidade();
		for (list<Obstaculo*>::iterator it = LOs.begin();it != LOs.end();it++) {
			po = *it;
			d = verificarDirecao(pJog1, po);
			if (d != 0) {

				po->obstacular(pJog1);


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




void Gerenciador_Colisoes::tratarColisoesJogsProjeteis() {
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
				pj->explodir(pJog1);

			}
		}

	}

}

void Gerenciador_Colisoes::tratarColisoesInimgsObstacs()
{
	//CHAMAR OBSTACULAR PARA PARAR O INIMIGO

	Obstaculo* po = NULL;
	Inimigo* pJog1 = NULL;
	int d = 0;
	for (int i = 0;i < LIs.size();i++) {
		pJog1 = LIs[i];
		pJog1->restaurarVelocidade();
		for (list<Obstaculo*>::iterator it = LOs.begin();it != LOs.end();it++) {
			po = *it;
			d = verificarDirecao(pJog1, po);
			if (d != 0) {

				//po->obstacular(pJog1);


				if (d == 1) {
					pJog1->getVel().y = 0.f;
					pJog1->getCorpo().setPosition(
						pJog1->getcm().x,
						po->getcm().y + pJog1->getRaio().y + po->getRaio().y
					);
				}
				if (d == 4) {
					pJog1->getVel().y = 0.f;
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

void Gerenciador_Colisoes::tratarColisoesInimgsProjeteis()
{
	Projetil* pj = NULL;
	Inimigo* pJog1 = NULL;
	int d = 0;
	for (int i = 0;i < LIs.size();i++) {
		pJog1 = LIs[i];

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
				pj->explodir(pJog1);

			}
		}

	}
}

void Gerenciador_Colisoes::tratarColisoesProjeteisObstacs()
{

	Obstaculo* po = NULL;
	Projetil* pj = NULL;
	int d = 0;
	for (set<Projetil*>::iterator it = LPs.begin();it != LPs.end();it++) {
		pj = *it;
		for (list<Obstaculo*>::iterator it = LOs.begin();it != LOs.end();it++) {
			po = *it;
			d = verificarDirecao(pj, po);
			if (d != 0) {
				pj->explodir();
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