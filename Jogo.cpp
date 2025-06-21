// Jogo.cpp
#include "Jogo.h"
#include "Fase1.h"  // Inclua a Fase1 aqui
#include "Fase2.h"
#include "json.hpp"
#include "MenuInicial.h"
#include <fstream>

using json = nlohmann::json;
using namespace Fases;
using namespace Entidades;

Jogo::Jogo()
    : GC(Gerenciadores::Gerenciador_Colisoes::getInstancia()),
    GG(Gerenciadores::Gerenciador_Grafico::getInstancia()),
    pF1(nullptr), pF2(nullptr)
{
    Ente::setpGG(GG);  // define ponteiro para o gerenciador gráfico na classe base

    sementear();

	executar(); // Chama o método executar para iniciar o jogo
}
Jogo::~Jogo()
{
    if (pF1)
        delete pF1;
    if (pF2)
        delete pF2;
    std::cout << "destrutora jogo" << std::endl;
}

void Jogo::executarFase() {
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
void Jogo::executar()
{
    sf::RenderWindow window(sf::VideoMode(960, 640), "Jogo");
    
    window.setFramerateLimit(60); // Limita para 60 FPS

    Gerenciadores::Gerenciador_Grafico::getInstancia()->setJanelaExterna(&window);

    MenuInicial menu;
    int escolha = menu.mostrar(window);
    int nJog = menu.getNJogadores();
    int fase = menu.getFase();

    
    srand(static_cast<unsigned int>(time(0))); // Semente para números aleatórios

    
    if (escolha == 0) {

        Fase* faseAtual = nullptr;
        std::ifstream in("save.json");
        json estado;
        in >> estado;

        int fase = estado.value("fase", 1); // valor padrão 1, caso não exista
        int nJog = estado.value("numPlayers", 1); // valor padrão 1, caso não exista

        numPlayers = nJog;

        // Cria a fase correta, mas não executa ainda
        if (fase == 1) {
            pF1 = new Fase1(GC, GG, nJog);
        }
        else {
            pF2 = new Fase2(GC, GG, nJog);
        }

        getFase()->carregarJogo("save.json");

        executarFase();
    }
    else if (escolha == 1) {
        //Jogo jogo(nJog, fase);

		numPlayers = nJog; // Define o número de jogadores

        if (fase == 1) {
            pF1 = new Fase1(GC, GG, nJog);
            getFase()->criarMapa("mapa1.json");
        }
        else if (fase == 2) {
            pF2 = new Fase2(GC, GG, nJog);
            getFase()->criarMapa("mapa2.json");
        }

        executarFase();
    }
    else {
        // Leaderboard
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

    Entidades::Personagens::Jogador::jogador1 = true;

    pF2 = new Fase2(GC, GG, numPlayers);
    pF2->criarMapa("mapa2.json");

    if (pF1) {
        delete pF1;
        pF1 = nullptr;
    }

    //pF2->setPontos1(pontos1);
    //pF2->setPontos2(pontos2);

    pF2->getJogador1()->setVida(0);
    pF2->getJogador1()->operator+=(pontos1);
    if (estado["numPlayers"] == 2) {
        pF2->getJogador2()->setVida(0);
        pF2->getJogador2()->operator+=(pontos2);
    }



    // Atualiza apenas vidas (sem reinserir ponteiros)
    if (pF2->getJogador1()) {
        pF2->getJogador1()->setVida(estado["jogador1"]["numvidas"]);
        //pF2->getJogador1()->operator+=(pontos1);
    }




    if (estado["numPlayers"] == 2 && pF2->getJogador2() && estado["jogador2"]["numvidas"] > 0) {
        pF2->getJogador2()->setVida(estado["jogador2"]["numvidas"]);
		//pF2->getJogador2()->operator+=(pontos2);
    }

    pF2->destruirNeutralizados(); // limpa neutralizados da fase 1

    executarFase();
}

void Jogo::sementear()
{
    time_t tempo;
	srand(static_cast<unsigned int>(time(&tempo))); 
}
