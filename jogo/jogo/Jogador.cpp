#include "Jogador.h"
bool Jogador::jogador1(true);

Jogador::Jogador(Vector2f pos) : Personagem(pos)
{
    agilidade = 2.f;
    if (jogador1) {
        /*
        if (!textura.loadFromFile("j1.png")) {
            std::cerr << "Erro ao carregar a textura JOGADOR1!" << std::endl;
        }
        else {
            corpo.setTexture(textura);
        }*/
        //corpo.setScale(0.1f, 0.1f);
        cout << "JOGADOR 1 CRIADO" << endl;
        corpo.setColor(Color::Blue);
        jogador1 = false;
        j1 = true;
    }
    else {
        /*
        if (!textura.loadFromFile("j2.png")) {
            std::cerr << "Erro ao carregar a textura JOGADOR2!" << std::endl;
        }
        else {
            corpo.setTexture(textura);
        }
        */
        //corpo.setScale(0.1f, 0.15f);
        cout << "JOGADOR 2 CRIADO" << endl;
        corpo.setColor(Color::Green);
        j1 = false;
    }

}

Jogador::~Jogador()
{
}

void Jogador::mover()
{
    //GRAVIDADE ANTES!
    if (getcm().y + getRaio().y < CHAO) {
        vel.y+= GRAVIDADE;
    }
    else {//chao
        vel.y =0;
    }
    if (j1) {
        if (getcm().y + getRaio().y < CHAO) {//NO AR

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
                vel.y += -PULO * agilidade;
            }
        }
    }
    else {//JOGADOR 2
        if (getcm().y + getRaio().y < CHAO) {//NO AR

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
                vel.y += -PULO * agilidade;
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

void Jogador::executar()
{
    mover();
}
