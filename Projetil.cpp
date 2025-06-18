#include "Projetil.h"

#include "Jogador.h"

Projetil::Projetil(Vector2f pos, bool dir, float raio, ListaEntidades* lp, Jogador* pdono) :
    Entidade(pos), ativo(true), lista(lp), duracao(TEMPO_PROJETIL), pDono(pdono)
{
    /*
    if (!textura.loadFromFile("boss.png")) {
        std::cerr << "Erro ao carregar a textura BOSS!" << std::endl;
    }
    else {
        corpo.setTexture(textura);
    }
    */
    corpo.setSize(Vector2f(50.f, 50.f));
    centralizarEntidade();
    corpo.setFillColor(Color::White);


    if (dir) {
        vel = (Vector2f(10.f, -10.f));
        corpo.move(raio * 1.5f, 0.f);
    }
    else {
        vel = (Vector2f(-10.f, -10.f));
        corpo.move(-raio * 1.5f, 0.f);
    }

}

Projetil::~Projetil()
{
    cout << "DESTRUTORA PROJETIL" << endl;
}

void Projetil::executar()
{
    vel.y += GRAVIDADE;
    corpo.move(vel);
    duracao--;
    if (duracao == 0) {
        cout << "acabou o tempo do projetil" << endl;
        ativo = false;
    }
}

void Projetil::salvar()
{
}

const bool Projetil::getAtivo()
{
    return ativo;
}

void Projetil::explodir(Personagem* pp)
{
    ativo = false;
    cout << "projetil colidiu" << endl;
    if (pp && pp != nullptr) {
        pp->operator--();
        if (pp && pp != nullptr && pp->getVidas() == 0) {
            cout << "personagem neutralizado por projetil" << endl;
            pDono->operator+=(100);
        }
    }

}

Vector2f Projetil::getVelocidade()
{
    return vel;
}

void Projetil::setVelocidade(Vector2f v)
{
    vel = v; 
}

Jogador* Projetil::getDono()
{
    return pDono;
}

void Projetil::setDono(Jogador* pdono)
{
    pDono = pdono;
}

