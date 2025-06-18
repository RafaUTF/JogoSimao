#include "Jogador.h"
bool Jogador::jogador1(true);


Jogador::Jogador(Vector2f pos) : Personagem(pos), pontos(0)
{
    num_vidas = VIDA_JOGADOR;

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
    cout << "destrutora jogador" << endl;

}

void Jogador::executar() {
    mover();
    atirar();
    tiros->percorrer();
}
float modulo(float x);
void Jogador::colidirJog(Jogador* p, int d)
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


void Jogador::atirar(short int f)
{
    if (recarga >= TEMPO_RECARGA) {
        if (j1 && sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            cout << "p1 ATIROU" << endl;
            tiros->incluir(new Projetil(getcm(), olhandoDir, getRaio().x, tiros, this, FORCA_JOG));
            recarga = 0;
        }
        else if (!j1 && sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            cout << "p2 ATIROU" << endl;
            tiros->incluir(new Projetil(getcm(), olhandoDir, getRaio().x, tiros, this, FORCA_JOG));
            recarga = 0;
        }
    }
    else
        recarga++;

}

const int Jogador::getPontos() const
{
    return pontos;
}

void Jogador::operator+=(const int n)
{
    pontos += n;
}

void Jogador::operator++()
{
    pontos++;
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
                vel.y += -PULO * 2 * agilidade;
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
                vel.y += -PULO * 2 * agilidade;
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