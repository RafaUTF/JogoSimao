#include "Jogador.h"
bool Jogador::jogador1(true);

Jogador::Jogador()
{
    agilidade = 2.f;
    if (jogador1) {
        corpo.setSize(sf::Vector2f(200.f, 100.f));
        corpo.setFillColor(sf::Color::Blue);
        corpo.setPosition(x, y);
        jogador1 = false;
        j1 = true;
    }
    else {
        corpo.setSize(sf::Vector2f(100.f, 200.f));
        corpo.setFillColor(sf::Color::Green);
        corpo.setPosition(x, y);
        j1 = false;
    }

}

Jogador::~Jogador()
{
}

void Jogador::mover()
{
    //GRAVIDADE ANTES!
    if (corpo.getPosition().y + corpo.getSize().y < CHAO) {
        vy += GRAVIDADE;
    }
    else {//chao
        vy = 0;
    }
    
    if (j1) {
        if (corpo.getPosition().y + corpo.getSize().y < CHAO) {//NO AR

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                vx += -agilidade / 5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                vx += agilidade / 5;

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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                vy += agilidade;
        }
        else if (corpo.getPosition().y < CHAO) {//CHAO

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                vx += -agilidade;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                cout << "pulo unico 2!" << endl;
                vy += -PULO * agilidade;
            }
        }
    }
    else{//JOGADOR 2
        
        if (corpo.getPosition().y + corpo.getSize().y < CHAO) {//NO AR

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                vx += -agilidade/5;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                vy += agilidade;
        }
        else if (corpo.getPosition().y < CHAO) {//CHAO

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                vx += -agilidade;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                cout << "pulo unico 2!" << endl;
                vy += - PULO * agilidade;
            }
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
    else if(vx < -MAX_VEL)
        vx = -MAX_VEL;
    corpo.move(vx, vy);
}
