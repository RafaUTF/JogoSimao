#include "Jogo.h"

Jogo::Jogo(): pJog1(new Jogador),pJog2(new Jogador),pInim(new Inimigo(pJog1,pJog2)),
GC(new Gerenciador_Colisoes)

{
    executar();
}

Jogo::~Jogo()
{
	delete pJog1;
	delete pJog2;
    delete pInim;
    delete GC;
}

void Jogo::executar()
{
    // Criação da janela
    sf::RenderWindow window(sf::VideoMode(1800, 900), "Quadrado em movimento - SFML 2.6.2");

    window.setFramerateLimit(60); // Limita a 60 FPS
    int i = 0;
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

        if (GC->verificarColisao(pJog1, pJog2))
            cout << i++ << endl;
        if (i > 200)
            i = 0;
        // Atualiza a tela
        window.clear(sf::Color::Black);
        window.draw(pJog1->getCorpo());
        window.draw(pJog2->getCorpo());
        window.draw(pInim->getCorpo());
        window.display();
    }

}
