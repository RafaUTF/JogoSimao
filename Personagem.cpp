#include "Personagem.h"

Personagem::Personagem(Vector2f pos) :
    Entidade(pos), num_vidas(VIDA_BASE),
    aceleracao(ACELERACAO_BASE), comChao(false), tiros(NULL),
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




void Personagem::atirar(short int f)
{
    if (recarga >= TEMPO_RECARGA) {
        cout << "CHEFAO ATIROU" << endl;
        tiros->incluir(new Projetil(getcm(), olhandoDir, getRaio().x, tiros, nullptr, f));
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
    aceleracao *= fator;

}

void Personagem::restaurarVelocidade() {
    aceleracao = 1.f;
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