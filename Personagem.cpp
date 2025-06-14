#include "Personagem.h"

Personagem::Personagem(Vector2f pos) :
Entidade(pos), num_vidas(VIDA_JOGADOR),
agilidade(5.f), comChao(false), tiros(NULL), 
recarga(TEMPO_RECARGA) ,olhandoDir(true)
{

}


Personagem::~Personagem()
{
    if (tiros) {
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
        tiros->incluir(new Projetil(getcm(), olhandoDir, getRaio().x,tiros));
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
