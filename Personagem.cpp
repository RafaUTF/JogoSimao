#include "Personagem.h"

Personagem::Personagem(Vector2f pos) :
    Entidade(pos), num_vidas(VIDA_BASE),
    agilidade(5.f), comChao(false), tiros(NULL),
    recarga(TEMPO_RECARGA), olhandoDir(true)
{

}


Personagem::~Personagem()
{

    if (tiros) {
        cout << "destrutora personagem apagando a lista de tiros" << endl;
        delete tiros;
        tiros = NULL;
    }
}

void Personagem::mover()
{
}

void Personagem::setChao(bool b)
{
    comChao = b;
}

ListaEntidades* Personagem::getTiros()
{
    return tiros;
}




void Personagem::atirar()
{
    if (recarga >= TEMPO_RECARGA) {
        cout << "CHEFAO ATIROU" << endl;
        tiros->incluir(new Projetil(getcm(), olhandoDir, getRaio().x, tiros, nullptr));
        recarga = 0;
    }
    else
        recarga++;

}

void Personagem::criarTiros()
{
    tiros = new ListaEntidades();
}

void Personagem::reduzVelocidade(float fator)
{
    agilidade *= fator;

}

void Personagem::restaurarVelocidade() {
    agilidade = 1.f;
}

void Personagem::sofrerGravidade()
{
}

void Personagem::operator--() {
    if (num_vidas > 0)
        num_vidas--;
}

const int Personagem::getVidas()
{
    return num_vidas;
}

void Personagem::setVida(int v)
{
	num_vidas = v;
}

void Personagem::colidir(Entidade* pe, int d)
{
    if (d == 1) {
        getVel().y = 0.f;
        getCorpo().setPosition(
            getcm().x,
            pe->getcm().y + getRaio().y + pe->getRaio().y
        );
    }

    else if (d == 2) {
        getVel().x = 0.f;
        getCorpo().setPosition(
            pe->getcm().x + getRaio().x + pe->getRaio().x,
            getcm().y
        );
    }
    else if (d == 3) {
        getVel().x = 0.f;
        getCorpo().setPosition(
            pe->getcm().x - getRaio().x - pe->getRaio().x,
            getcm().y
        );
    }
    else {//d==4
        comChao = true;
        getVel().y = 0.f;
        getVel().y = pe->getVel().y;
        getCorpo().setPosition(
            getcm().x,
            pe->getcm().y - getRaio().y - pe->getRaio().y
        );
    }

}

void Personagem::incluirTiros(Projetil* p)
{
    if (tiros == NULL) {
        cout << "criando lista de tiros" << endl;
        criarTiros();
    }
	tiros->incluir(p);
}

/*
if (d == 1) {
    //chao2 = true;
    p2->getVel().y = p1->getVel().y;
    p1->getCorpo().move(0.f, y / 2);
    p2->getCorpo().move(0.f, -y / 2);

}
if (d == 4) {
    //chao1 = true;
    p1->getVel().y = p2->getVel().y;
    p1->getCorpo().move(0.f, -y / 2);
    p2->getCorpo().move(0.f, y / 2);

}

if (d == 2) {
    p1->getVel().x = 0.f;
    p2->getVel().x = 0.f;
    p1->getCorpo().move(x / 2, 0.f);
    p2->getCorpo().move(-x / 2, 0.f);

}
if (d == 3) {
    p1->getVel().x = 0.f;
    p2->getVel().x = 0.f;

    p1->getCorpo().move(-x / 2, 0.f);
    p2->getCorpo().move(x / 2, 0.f);

}*/