#include "Jogo.h"
#include "Fase1.h"  // Inclua a Fase1 aqui

Jogo::Jogo(int numPlayers_, int fase_) :
    GC(Gerenciador_Colisoes::getInstancia()),
    GG(Gerenciador_Grafico::getInstancia()),
    numPlayers(numPlayers_),
    fase(fase_),
    pFase(nullptr)
{
    Ente::setpGG(GG);  // define ponteiro para o gerenciador gráfico na classe base
    // Cria a fase correta
    if (fase == 1) {
        pFase = new Fase1(GC, GG, numPlayers);
    }
    else
        std::cout << "Fase " << fase << " ainda não implementada.\n";

    executar();
}

Jogo::~Jogo()
{
    delete pFase;
}

void Jogo::executar()
{

    if (pFase)
        pFase->executar();
}
