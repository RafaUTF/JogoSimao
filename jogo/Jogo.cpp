#include "Jogo.h"

Jogo::Jogo(): 
    pJog1(new Jogador( Vector2f(150.f,150.f) ) ),
    pJog2(new Jogador(Vector2f(500.f, 150.f))),
    pInim(new Inimigo(pJog1,pJog2, (Vector2f(800.f, 300.f)) )),
    GC(new Gerenciador_Colisoes), 
    GG(new Gerenciador_Grafico)
    //pPlat(new Plataforma)
{
    
    lista.incluir(pJog1);
    lista.incluir(pJog2);
    lista.incluir(pInim);
    //lista.incluir(pPlat);
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
    //GG->getWindow().setFramerateLimit(60); // Limita a 60 FPS
   // window.setFramerateLimit(60); // Limita a 60 FPS

    int i = 0;
    // Loop principal
    while (GG->aberta())
    {
        sf::Event event;
        while (GG->getWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GG->fechar();
        }

        lista.percorrer();//por enquanto move tudo
        //pJog1->mover();
        //pJog2->mover();
        //pInim->mover();

        if (GC->verificarColisao(pJog1, pJog2))
            cout << i++ << endl;
        if (i > 200)
            i = 0;
        // Atualiza a tela
        GG->clear();
        GG->desenhaFundo();


        //lista.desenhar();//nao funciona


        GG->desenhar(pJog1);
        GG->desenhar(pJog2);
        GG->desenhar(pInim);


        //GG->getWindow().draw(pPlat->getCorpo());
        GG->mostrar();
    }

}
