#include "Jogo.h"

Jogo::Jogo(): pJog1(new Jogador),pJog2(new Jogador),pInim(new Inimigo(pJog1,pJog2)),
GC(new Gerenciador_Colisoes), GG(new Gerenciador_Grafico)
{
    lista.incluir(pJog1);
    lista.incluir(pJog2);
    lista.incluir(pInim);
    executar();
}

Jogo::~Jogo()
{
    //lista já deleta tudo;
    /*
	delete pJog1;
	delete pJog2;
    delete pInim;
    */
    delete GC;
    delete GG;
}

void Jogo::executar()
{
    // Criação da janela
    //sf::RenderWindow window(sf::VideoMode(1800, 900), "Quadrado em movimento - SFML 2.6.2");
    GG->getWindow().setFramerateLimit(60); // Limita a 60 FPS
   // window.setFramerateLimit(60); // Limita a 60 FPS
    int i = 0;
    // Loop principal
    while (GG->getWindow().isOpen())
    {
        sf::Event event;
        while (GG->getWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GG->getWindow().close();
        }
        lista.percorrer();//por enquanto move tudo
        ///pJog1->mover();
        //pJog2->mover();
        //pInim->mover();

        if (GC->verificarColisao(pJog1, pJog2))
            cout << i++ << endl;
        if (i > 200)
            i = 0;
        // Atualiza a tela
        GG->getWindow().clear(sf::Color::Black);

        //lista.desenhar();//queria fazer mas nao deu

        GG->getWindow().draw(pJog1->getCorpo());
        GG->getWindow().draw(pJog2->getCorpo());
        GG->getWindow().draw(pInim->getCorpo());
        GG->getWindow().display();
    }

}
