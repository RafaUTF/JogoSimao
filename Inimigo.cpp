#include "Inimigo.h"

Inimigo::Inimigo(Vector2f pos) :
    Personagem(pos), pAlvo(nullptr), p1(nullptr), p2(nullptr),
    nivel_maldade(NIVEL_MALDADE_BASICO), chefao(false)
{
    agilidade = 1.f;

    corpo.setSize(Vector2f(150.f, 70.f));
    centralizarEntidade();

}

Inimigo::~Inimigo()
{

}

void Inimigo::executar()
{
    mover();
}

void Inimigo::danificar(Jogador* p, int d)
{
    cout << "atacou" << endl;
    if (p) {
        for (int i = 0; i < nivel_maldade; i++) {
            p->operator--();
        }
        if (d == 1) {
            p->getVel().y = 0.f;
            p->getCorpo().setPosition(
                p->getcm().x,
                getcm().y + p->getRaio().y + getRaio().y
            );
        }
        if (d == 2) {
            p->getVel().x = 0.f;
            p->getCorpo().setPosition(
                getcm().x + p->getRaio().x + getRaio().x + ELASTICIDADE_INIMIGO,
                p->getcm().y
            );
        }
        if (d == 3) {
            p->getVel().x = 0.f;
            p->getCorpo().setPosition(
                getcm().x - p->getRaio().x - getRaio().x - ELASTICIDADE_INIMIGO,
                p->getcm().y
            );
        }
    }
    else {
        cout << "jogador nulo" << endl;
    }
}

void Inimigo::escolherAlvo()
{
    pAlvo = nullptr;
    float dx1 = p1->getcm().x - getcm().x,
        dy1 = p1->getcm().y - getcm().y,
        dquadrado1 = dx1 * dx1 + dy1 * dy1;
    if (p2) {
        float dx2 = p2->getcm().x - getcm().x,
            dy2 = p2->getcm().y - getcm().y,
            dquadrado2 = dx2 * dx2 + dy2 * dy2;

        if (dquadrado1 > dquadrado2) {
            if (dquadrado2 < VISAO_INIMIGO2)
                pAlvo = p2;
            else
                pAlvo = nullptr;
        }
        else if (dquadrado1 < VISAO_INIMIGO2) {
            pAlvo = p1;
        }
    }
    else {//so tem o jogador1
        if (dquadrado1 < VISAO_INIMIGO2)
            pAlvo = p1;
    }
}

void Inimigo::perseguir()
{
    if (!comChao) {//NO AR

        if (pAlvo->getcm().x < getcm().x)
            vel.x += -agilidade / 5;
        if (pAlvo->getcm().x > getcm().x)
            vel.x += agilidade / 5;

        //ATRITO AR(VISCOSO)
        if (vel.x > 0) {
            vel.x -= VISCOSO;
            if (vel.x < 0)
                vel.x = 0.f;
        }
        else if (vel.x < 0) {
            vel.x += VISCOSO;
            if (vel.x > 0)
                vel.x = 0.f;
        }
        if (pAlvo->getcm().y > getcm().y)
            vel.y += agilidade;
    }
    else if (getcm().y - getRaio().y < CHAO) {//CHAO

        if (pAlvo->getcm().x < getcm().x)
            vel.x += -agilidade;
        if (pAlvo->getcm().x > getcm().x)
            vel.x += agilidade;

        //ATRITO CHAO
        if (vel.x > 0) {
            vel.x -= ATRITO;
            if (vel.x < 0)
                vel.x = 0.f;
        }
        else if (vel.x < 0) {
            vel.x += ATRITO;
            if (vel.x > 0)
                vel.x = 0.f;
        }
        if (pAlvo->getcm().y < getcm().y) {
            //cout << "pulo unico 2!" << endl;
            vel.y += -PULO * 2 * agilidade;
            comChao = false;
        }
    }

    //
    /*
    if (getcm().y + getRaio().y < CHAO_CHEFE) {//NO AR

        if (pAlvo->getcm().x < getcm().x)
            vel.x += -agilidade / 5;
        if (pAlvo->getcm().x > getcm().x)
            vel.x += agilidade / 5;

        //ATRITO AR(VISCOSO)
        if (vel.x > 0) {
            vel.x -= VISCOSO;
            if (vel.x < 0)
                vel.x = 0.f;
        }
        else if (vel.x < 0) {
            vel.x += VISCOSO;
            if (vel.x > 0)
                vel.x = 0.f;
        }
        if (pAlvo->getcm().y > getcm().y)
            vel.y += agilidade / 5;
    }
    else if (getcm().y - getRaio().y < CHAO_CHEFE) {//chao

        if (pAlvo->getcm().x < getcm().x)
            vel.x += -agilidade;
        if (pAlvo->getcm().x > getcm().x)
            vel.x += agilidade;

        //ATRITO CHAO
        if (vel.x > 0) {
            vel.x -= ATRITO;
            if (vel.x < 0)
                vel.x = 0.f;
        }
        else if (vel.x < 0) {
            vel.x += ATRITO;
            if (vel.x > 0)
                vel.x = 0.f;
        }

        if (pAlvo->getcm().y < getcm().y) {
            //cout << "pulo unico inimigo!" << endl;
            vel.y += -PULO * agilidade;
        }
    }
    */

    //////

    //atrito do ar em y
    if (vel.y > 0) {
        vel.y -= VISCOSO;
        if (vel.y < 0)
            vel.y = 0.f;
    }
    else if (vel.y < 0) {
        vel.y += VISCOSO;
        if (vel.y > 0)
            vel.y = 0.f;
    }

    //paredes invisiveis
    //if (getcm().x - getRaio().x < ESQUERDA && vel.x<0
    //   || getcm().x + getRaio().x > DIREITA && vel.x>0) {
    //    vel.x = 0.f;
    //}

    if (vel.x > MAX_VEL)
        vel.x = MAX_VEL;
    else if (vel.x < -MAX_VEL)
        vel.x = -MAX_VEL;

    if (vel.x > 0)
        olhandoDir = true;
    else if (vel.x < 0)
        olhandoDir = false;
}
float modulo(float x);
void Inimigo::colidirInim(Inimigo* p, int d)
{
    float dx = p->getcm().x - getcm().x,//+ -> colisao dir do pe1
        dy = p->getcm().y - getcm().y,//+ -> colisao em baixo do pe1
        drx = getRaio().x + p->getRaio().x,
        dry = getRaio().y + p->getRaio().y,
        x = drx - modulo(dx), y = dry - modulo(dy);

    if (d == 1) {
        //chao2 = true;
        p->setChao(true);
        p->getVel().y = getVel().y;
        getCorpo().move(0.f, y / 2);
        p->getCorpo().move(0.f, -y / 2);

    }
    if (d == 4) {
        //chao1 = true;
        setChao(true);
        getVel().y = p->getVel().y;
        getCorpo().move(0.f, -y / 2);
        p->getCorpo().move(0.f, y / 2);

    }
    if (d == 2) {
        getVel().x = 0.f;
        p->getVel().x = 0.f;
        getCorpo().move(x / 2, 0.f);
        p->getCorpo().move(-x / 2, 0.f);

    }
    if (d == 3) {
        getVel().x = 0.f;
        p->getVel().x = 0.f;

        getCorpo().move(-x / 2, 0.f);
        p->getCorpo().move(x / 2, 0.f);

    }
}