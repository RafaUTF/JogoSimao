// Jogo.cpp
#include "Jogo.h"
#include "Fase1.h"  // Inclua a Fase1 aqui
#include "Fase2.h"

Jogo::Jogo(int numPlayers_, int fase_)
    : GC(Gerenciador_Colisoes::getInstancia()),
    GG(Gerenciador_Grafico::getInstancia()),
    numPlayers(numPlayers_),
    fase(fase_),
    pF1(nullptr), pF2(nullptr)
{
    Ente::setpGG(GG);  // define ponteiro para o gerenciador gráfico na classe base

    // Cria a fase correta, mas não executa ainda
    if (fase == 1) {
        pF1 = new Fase1(GC, GG, numPlayers);
    }
    else {
        pF2 = new Fase2(GC, GG, numPlayers);
    }
}

Jogo::~Jogo()
{
    if (pF1)
        delete pF1;
    if (pF2)
        delete pF2;
    std::cout << "destrutora jogo" << std::endl;
}

void Jogo::executar()
{
    // Inicia loop da fase criada
    if (pF1)
        pF1->executar();
    else if (pF2)
        pF2->executar();
}

Fase* Jogo::getFase()
{
    if(pF1)
        return pF1;
    else if(pF2)
		return pF2;
}
