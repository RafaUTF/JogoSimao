#include "Inimigo.h"

Inimigo::Inimigo(Jogador* pp1, Jogador* pp2):p1(pp1),p2(pp2),nivel_maldade(0)
{
    agilidade = 2.f;

    corpo.setSize(sf::Vector2f(50.f, 50.f));
    corpo.setFillColor(sf::Color::Red);
    corpo.setPosition(x, y);
}

Inimigo::~Inimigo()
{
}

void Inimigo::mover()
{

    float dx1 = p1->getXcm(),
        dy1 = p1->getYcm(),
        dx2 = p2->getXcm(),
        dy2 = p2->getYcm();

    Jogador* p = p2;
    if (dx1 * dx1 + dy1 * dy1 > dx2 * dx2 + dy2 * dy2)
        p = p1;


    //GRAVIDADE ANTES!
    if (corpo.getPosition().y + corpo.getSize().y < CHAO) {
        vy += GRAVIDADE;
    }
    else {//chao
        vy = 0;
    }

    if (corpo.getPosition().y + corpo.getSize().y < CHAO) {//NO AR

        if (p->getXcm() < corpo.getPosition().x)
            vx += -agilidade/5;
        if (p->getXcm() > corpo.getPosition().x)
            vx += agilidade/5;

        //ATRITO AR(VISCOSO)
        if (vx > 0) {
            vx -= VISCOSO;
            if (vx < 0)
                vx = 0.f;
        }
        else if (vx < 0) {
            vx += VISCOSO;
            if (vx > 0)
                vx = 0.f;
        }
        if (p->getYcm() > corpo.getPosition().y)
            vy += agilidade/5;
    }
    else if (corpo.getPosition().y < CHAO) {//chao

        if (p->getXcm() < corpo.getPosition().x)
            vx += -agilidade;
        if (p->getXcm() > corpo.getPosition().x)
            vx += agilidade;

        //ATRITO CHAO
        if (vx > 0) {
            vx -= ATRITO;
            if (vx < 0)
                vx = 0.f;
        }
        else if (vx < 0) {
            vx += ATRITO;
            if (vx > 0)
                vx = 0.f;
        }

        if (p->getYcm() < corpo.getPosition().y) {
            //cout << "pulo unico inimigo!" << endl;
            vy += - PULO * agilidade;
        }
    }

    //atrito do ar em y

    if (vy > 0) {
        vy -= VISCOSO;
        if (vy < 0)
            vy = 0.f;
    }
    else if (vy < 0) {
        vy += VISCOSO;
        if (vy > 0)
            vy = 0.f;
    }

    //paredes invisiveis
    if (corpo.getPosition().x < ESQUERDA && vx<0
        || corpo.getPosition().x + corpo.getSize().x > DIREITA && vx>0) {
        vx = 0.f;
    }
    if (vx > MAX_VEL)
        vx = MAX_VEL;
    else if (vx < -MAX_VEL)
        vx = -MAX_VEL;
    corpo.move(vx, vy);
}

void Inimigo::executar()
{
    mover();
}
