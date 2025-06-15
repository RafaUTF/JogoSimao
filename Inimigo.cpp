#include "Inimigo.h"

Inimigo::Inimigo(Vector2f pos) :
    Personagem(pos), nivel_maldade(0), pAlvo(nullptr), p1(nullptr), p2(nullptr)
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

void Inimigo::danificar(Jogador* p)
{
    cout << "atacou" << endl;
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
    if (getcm().y + getRaio().y < CHAO) {//NO AR

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
    else if (getcm().y - getRaio().y < CHAO) {//chao

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

    if (vel.x > MAX_VEL)
        vel.x = MAX_VEL;
    else if (vel.x < -MAX_VEL)
        vel.x = -MAX_VEL;


    if (vel.x > 0)
        olhandoDir = true;
    else if (vel.x < 0)
        olhandoDir = false;
}
