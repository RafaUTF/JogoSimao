#include "Projetil.h"

#include "Jogador.h"

using namespace Listas;

namespace Entidades {

    Projetil::Projetil(Vector2f pos, bool dir, float raio, Listas::ListaEntidades* lp, Entidades::Personagens::Jogador* pdono,
        short int f) :
        Entidade(pos), ativo(true), lista(lp), duracao(TEMPO_PROJETIL), pDono(pdono)
    {
        try {
            carregarTextura("boss.png");
            corpo.setTexture(&textura);
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            corpo.setFillColor(sf::Color::White); // fallback color
        }

        if (dynamic_cast<Personagens::Jogador*>(pDono)) {
            corpo.setSize(Vector2f(TAM_PROJ_JOG, TAM_PROJ_JOG));
        }
        else {
            corpo.setSize(Vector2f(TAM_PROJ_CHEFE, TAM_PROJ_CHEFE));
        }
        centralizarEntidade();

        float v = static_cast<float>(f);
        if (dir) {
            vel = (Vector2f(v, VY0));
            corpo.move(raio * 1.5f, 0.f);
        }
        else {
            vel = (Vector2f(-1.f * v, VY0));
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

    void Projetil::explodir(Entidades::Personagens::Personagem* pp)
    {
        ativo = false;
        cout << "projetil colidiu" << endl;
        if (pp && pp != nullptr) {
            pp->operator--();
            if (pp && pp != nullptr && pp->getVidas() == 0) {
                cout << "personagem neutralizado por projetil" << endl;
                if (pDono)
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

    void Projetil::setDono(Entidades::Personagens::Jogador* pdono)
    {
        pDono = pdono;
    }

}
