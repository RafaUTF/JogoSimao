#include "Jogo.h"

Jogo::Jogo(): 
    pJog1(new Jogador( Vector2f(150.f,150.f) ) ),
    pJog2(new Jogador(Vector2f(500.f, 150.f))),
    //pJog2(NULL),
    pInim(new Inimigo(pJog1,pJog2, (Vector2f(800.f, 300.f)) )),
    pPlat1(new Plataforma(Vector2f(800.f, 550.f))),
    pPlat2(new Plataforma(Vector2f(600.f, 650.f))),
    GC(Gerenciador_Colisoes::getInstancia()),
    GG(Gerenciador_Grafico::getInstancia())//
{
    
    Ente::setpGG(Gerenciador_Grafico::getInstancia());

    lista.incluir(pJog1);
    lista.incluir(pJog2);
    lista.incluir(pInim);
    lista.incluir(pPlat1);
    lista.incluir(pPlat2);

    GC->incluirJogador(pJog1);
    GC->incluirJogador(pJog2);
    GC->incluirObstaculo(pPlat1);
    GC->incluirObstaculo(pPlat2);
    GC->incluirInimigo(pInim);

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

    //delete GC;

    //delete GG;
}

void Jogo::executar()
{
    
    int i = 0,d=0,da=0;
    //Vector2f v(0.f, 0.f);
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
    
        /*
        v = GC->verificarDirecao(pJog1, pJog2);
        if (v != Vector2f(0.f, 0.f)) {
            cout <<"X: " << v.x << "      Y: " << v.y  << "  " << i++ << endl;
            if (i > 200)
                i = 0;
            if (v.x == 0.f) {
                pJog2->setChao(true);
            }
            else {
                pJog2->setChao(false);
            }
        }
        */
        //GC->executar();

        //GC->tratarColisoesJogs();
        //GC->tratarColisoesJogsObstacs();
        GC->executar();
        
        ListaEntidades& l = pJog1->getTiros();
        for (l.primeiro();!l.fim();l.operator++()) {
            GC->incluirProjetil(static_cast<Projetil*>(l.getAtual()));
        }

        ListaEntidades& l2 = pJog2->getTiros();
        for (l2.primeiro();!l2.fim();l2.operator++()) {
            GC->incluirProjetil(static_cast<Projetil*>(l2.getAtual()));
        }

        /*
        da = d;
        d = GC->verificarDirecao(pJog1, pJog2);
        cout << d << "    " << i++ << endl;
        if (i > 200)
            i = 0;
        GC->tratarColisoesJogs();
        if (d != 0) {
            if (d==1) {
                pJog2->setChao(true);
                pJog2->getCorpo().setPosition(
                    pJog2->getcm().x,
                    pJog1->getcm().y - pJog1->getRaio().y - pJog2->getRaio().y
                );
            }
            if (d == 4) {
                pJog1->setChao(true);
                pJog1->getCorpo().setPosition(
                    pJog1->getcm().x,
                    pJog2->getcm().y - pJog1->getRaio().y - pJog2->getRaio().y
                );
            }
            if (d == 2) {
                pJog1->getCorpo().setPosition(
                    pJog2->getcm().x + pJog1->getRaio().x + pJog2->getRaio().x,
                    pJog1->getcm().y
                );
                pJog2->getCorpo().setPosition(
                    pJog1->getcm().x - pJog1->getRaio().x - pJog2->getRaio().x,
                    pJog2->getcm().y
                );
            }
            if (d == 3) {
                pJog1->getCorpo().setPosition(
                    pJog2->getcm().x - pJog1->getRaio().x - pJog2->getRaio().x,
                    pJog1->getcm().y
                );
                pJog2->getCorpo().setPosition(
                    pJog1->getcm().x + pJog1->getRaio().x + pJog2->getRaio().x,
                    pJog2->getcm().y
                );
            }
          
        }
        if (da != d) {
            pJog2->setChao(false);
            pJog1->setChao(false);
        }
        /*
        if (v.x == 0.f) {
            //compara as massas...
            //if(M>>m)
            pJog2->getCorpo().setPosition(
                pJog2->getCorpo().getPosition().x,
                pJog1->getcm().y- pJog2->getRaio().y - pJog1->getRaio().y-1.f
                );

        }*/
       
        /*//colisao elastica
            Vector2f v2(-v);
            if (pJog1->getcm().y + pJog1->getRaio().y + v.y / 10.f > CHAO)
                v.y = 0.f;
            pJog1->getCorpo().move(v.x / 10.f, v.y / 10.f);

            if (pJog2->getcm().y + pJog2->getRaio().y + v2.y / 10.f > CHAO)
                v2.y = 0.f;
            pJog2->getCorpo().move(v2.x / 10.f, v2.y / 10.f);
        */
        // Atualiza a tela
        GG->clear();
        GG->desenhaFundo();


        lista.desenhar();
        pJog1->getTiros().desenhar();
        pJog2->getTiros().desenhar();
        GG->mostrar();
    }

}
