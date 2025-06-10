#include "Jogador.h"
bool Jogador::jogador1(true);


Jogador::Jogador(Vector2f pos) : Personagem(pos)
{
    agilidade = 1.f;

    criarTiros();

    if (jogador1) {
        
        if (!textura.loadFromFile("j1.png")) {
            std::cerr << "Erro ao carregar a textura JOGADOR1!" << std::endl;
        }
        else {
            corpo.setTexture(&textura);
        }
        cout << "JOGADOR 1 CRIADO" << endl;
        corpo.setSize(Vector2f(64.f, 64.f));
        centralizarEntidade();
        jogador1 = false;
        j1 = true;
    }
    else {
        
        if (!textura.loadFromFile("j2.png")) {
            std::cerr << "Erro ao carregar a textura JOGADOR2!" << std::endl;
        }
        else {
            corpo.setTexture(&textura);
        }
       
        cout << "JOGADOR 2 CRIADO" << endl;
        corpo.setSize(Vector2f(64.f, 64.f));
        centralizarEntidade();

     
        j1 = false;
    }

}
Jogador::~Jogador()
{

}

void Jogador::executar() {
    mover();
    atirar();
    tiros->percorrer();
}
float modulo2(float x) {
    return x < 0 ? (-1.f) * x : x;
}

void Jogador::colidir(Jogador* p)//bom para o inimigo
{
    float dx = p->getcm().x - getcm().x,//+ -> colisao dir do pe1
        dy = p->getcm().y - getcm().y,//+ -> colisao em baixo do pe1
        drx = getRaio().x + p->getRaio().x,
        dry = getRaio().y + p->getRaio().y;

    if (modulo2(dx) < drx && modulo2(dy) < dry) {
        if (drx - modulo2(dx) < dry - modulo2(dy)) {//colisao lado
            if (dx > 0) {//dir pe1  3
                corpo.setPosition(
                    p->getcm().x - getRaio().x - p->getRaio().x,
                    getcm().y
                );
            }
            else {//esq pe1  2
                corpo.setPosition(
                    p->getcm().x + getRaio().x + p->getRaio().x,
                    getcm().y
                );
            }
        }
        else {//colisao vertical
            if (dy > 0) {//baixo pe1  4
                setChao(true);
                corpo.setPosition(
                    getcm().x,
                    p->getcm().y - getRaio().y - p->getRaio().y
                );

            }
            else {//cima pe1    1
                //p->setChao(true);//////////////
                corpo.setPosition(
                    getcm().x,
                    p->getcm().y + getRaio().y + p->getRaio().y
                );
            }
        }
    }
}

void Jogador::atirar()
{
    if (recarga >= TEMPO_RECARGA) {
        if (j1 && sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            cout << "p1 ATIROU" << endl;
            tiros->incluir(new Projetil(getcm(),olhandoDir,getRaio().x,tiros));
            recarga = 0;
        }
        else if (!j1&&sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            cout << "p2 ATIROU" << endl;
            tiros->incluir(new Projetil(getcm(), olhandoDir, getRaio().x,tiros));
            recarga = 0;
        }
    }
    else
        recarga++;

}

void Jogador::mover()
{
    
    //GRAVIDADE ANTES!
    if (getcm().y + getRaio().y < CHAO && !comChao) {
        vel.y += GRAVIDADE;
    }
    else {//chao // comChao == true
        vel.y = 0;
        comChao = true;//tem q ter!
    }
    if (j1) {
        if (!comChao) {//NO AR

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                vel.x += -agilidade / 5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                vel.y += agilidade;
        }
        else if (getcm().y - getRaio().y < CHAO) {//CHAO

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                vel.x += -agilidade;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                //cout << "pulo unico 2!" << endl;
                vel.y += -PULO * 2*agilidade;
                comChao = false;
            }
        }
    }
    else {//JOGADOR 2
        if (!comChao) {//NO AR

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                vel.x += -agilidade / 5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                vel.y += agilidade;
        }
        else if (getcm().y - getRaio().y < CHAO) {//CHAO

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                vel.x += -agilidade;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                //cout << "pulo unico 2!" << endl;
                vel.y += -PULO * 2* agilidade;
                comChao = false;
            }
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
    //if (getcm().x - getRaio().x < ESQUERDA && vel.x<0
    //   || getcm().x + getRaio().x > DIREITA && vel.x>0) {
    //    vel.x = 0.f;
    //}

    if (vel.x > MAX_VEL)
        vel.x = MAX_VEL;
    else if (vel.x < -MAX_VEL)
        vel.x = -MAX_VEL;

    corpo.move(vel);

    if (vel.x > 0)
        olhandoDir = true;
    else if (vel.x < 0)
        olhandoDir = false;
}


void Jogador::operator--() {
    if (num_vidas > 0)
        num_vidas--;
}
