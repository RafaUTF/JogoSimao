#include "Jogo.h"
#include "Fase1.h"  // Inclua a Fase1 aqui

Jogo::Jogo(int numPlayers_, int fase_) :
    GC(Gerenciador_Colisoes::getInstancia()),
    GG(Gerenciador_Grafico::getInstancia()),
    numPlayers(numPlayers_),
    fase(fase_),
    pF1(nullptr),pF2(nullptr)
{
    Ente::setpGG(GG);  // define ponteiro para o gerenciador gráfico na classe base
    // Cria a fase correta
    if (fase == 1) {
        pF1 = new Fase1(GC, GG, numPlayers);
    }
    else {
        pF2 = new Fase2(GC, GG, numPlayers);
        //std::cout << "Fase " << fase << " ainda não implementada.\n";
    }

    executar();
}

Jogo::~Jogo()
{
    if(pF1)
        delete pF1;
    if (pF2)
        delete pF2;
    
}

void Jogo::executar()
{
    if (pF1)
        pF1->executar();
    else if (pF2)
        pF2->executar();
}
