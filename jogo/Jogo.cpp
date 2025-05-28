#include "Jogo.h"

Jogo::Jogo(): pJog1(new Jogador),pJog2(new Jogador),pInim(new Inimigo(pJog1,pJog2))
{

    executar();
}

Jogo::~Jogo()
{
	delete pJog1;
	delete pJog2;
    delete pInim;
}

void Jogo::executar()
{
    // Criação da janela
    sf::RenderWindow window(sf::VideoMode(1800, 900), "Quadrado em movimento - SFML 2.6.2");

    window.setFramerateLimit(60); // Limita a 60 FPS

    // Loop principal
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        pJog1->mover();
        pJog2->mover();
        pInim->mover();
        // Atualiza a tela
        window.clear(sf::Color::Black);
        window.draw(pJog1->getCorpo());
        window.draw(pJog2->getCorpo());
        window.draw(pInim->getCorpo());
        window.display();
    }

}
