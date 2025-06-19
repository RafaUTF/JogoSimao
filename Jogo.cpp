// Jogo.cpp
#include "Jogo.h"
#include "Fase1.h"  // Inclua a Fase1 aqui
#include "Fase2.h"
#include "json.hpp"

using json = nlohmann::json;

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

void Jogo::executar() {
    while (true) {
        if (pF1) {
            pF1->executar();
            if (pF1->deveTrocarFase()) {
                mudarParaFase2("save.json"); // define e executa Fase2
                break;
            }
            else break; // terminou normalmente
        }
        else if (pF2) {
            pF2->executar();
            break; // jogo terminou aqui
        }
    }
}
Fase* Jogo::getFase()
{
    if(pF1)
        return pF1;
    else if(pF2)
		return pF2;
}

void Jogo::mudarParaFase2(const std::string& caminho)
{
    json estado;

    std::ifstream in(caminho);
    if (in.is_open()) {
        in >> estado;
    }

    int pontos1 = pF1->getPontos1();
    int pontos2 = pF1->getPontos2();

    Jogador::jogador1 = true;

    pF2 = new Fase2(GC, GG, numPlayers);
    pF2->criarMapa("mapa2.json");

    if (pF1) {
        delete pF1;
        pF1 = nullptr;
    }

    pF2->setPontos1(pontos1);
    pF2->setPontos2(pontos2);

    pF2->getJogador1()->setVida(0);
    if (estado["numPlayers"] == 2)
        pF2->getJogador2()->setVida(0);

    cout << "VIdas2" << pF2->getJogador2()->getVidas() << endl;

    // Atualiza apenas vidas (sem reinserir ponteiros)
    if (pF2->getJogador1())
        pF2->getJogador1()->setVida(estado["jogador1"]["numvidas"]);


    cout << "VIdas2" << pF2->getJogador2()->getVidas() << endl;

    if (estado["numPlayers"] == 2 && pF2->getJogador2() && estado["jogador2"]["numvidas"] > 0)
        pF2->getJogador2()->setVida(estado["jogador2"]["numvidas"]);

    cout << "VIdas2" << pF2->getJogador2()->getVidas() << endl;

    pF2->destruirNeutralizados(); // limpa neutralizados da fase 1


    executar();
}