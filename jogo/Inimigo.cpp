#include "Inimigo.h"

Inimigo::Inimigo(Jogador* pp1, Jogador* pp2, Vector2f pos) :
    Personagem(pos),
    p1(pp1),p2(pp2),nivel_maldade(0)
{
    agilidade = 2.f;
    /*
    if (!textura.loadFromFile("boss.png")) {
        std::cerr << "Erro ao carregar a textura BOSS!" << std::endl;
    }
    else {
        corpo.setTexture(textura);
    }
    */
    corpo.setSize(Vector2f(150.f, 70.f));
    centralizarEntidade();
    corpo.setFillColor(Color::Red);
}

Inimigo::~Inimigo()
{
}

void Inimigo::mover()
{
    //getcm()
    float dx1 = p1->getcm().x,
        dy1 = p1->getcm().y,
        dx2 = p2->getcm().x,
        dy2 = p2->getcm().y;

    Jogador* p = p2;
    if (dx1 * dx1 + dy1 * dy1 > dx2 * dx2 + dy2 * dy2)
        p = p1;


    //GRAVIDADE ANTES!
    if (getcm().y + getRaio().y < CHAO) {
        vel.y += GRAVIDADE;
    }
    else {//chao
        vel.y = 0;
    }

    if (getcm().y + getRaio().y < CHAO) {//NO AR

        if (p->getcm().x < getcm().x)
            vel.x += -agilidade/5;
        if (p->getcm().x > getcm().x)
            vel.x += agilidade/5;

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
        if (p->getcm().y > getcm().y)
            vel.y += agilidade/5;
    }
    else if (getcm().y - getRaio().y < CHAO) {//chao

        if (p->getcm().x < getcm().x)
            vel.x += -agilidade;
        if (p->getcm().x > getcm().x)
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

        if (p->getcm().y < getcm().y) {
            //cout << "pulo unico inimigo!" << endl;
            vel.y += - PULO * agilidade;
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

    //paredes invisiveis
    if (getcm().x - getRaio().x < ESQUERDA && vel.x<0
        || getcm().x + getRaio().x > DIREITA && vel.x>0) {
        vel.x = 0.f;
    }
    if (vel.x > MAX_VEL)
        vel.x = MAX_VEL;
    else if (vel.x < -MAX_VEL)
        vel.x = -MAX_VEL;

    corpo.move(vel);
}

void Inimigo::executar()
{
    mover();
}
