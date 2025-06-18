#include "Jogo.h"
#include "MenuInicial.h"
#include "json.hpp"

using json = nlohmann::json;

int main()
{
    sf::RenderWindow window(sf::VideoMode(960, 640), "Jogo");
    window.setFramerateLimit(60); // Limita para 60 FPS


    Gerenciador_Grafico::getInstancia()->setJanelaExterna(&window);


    MenuInicial menu;
    int escolha = menu.mostrar(window);
    int nJog = menu.getNJogadores();
    int fase = menu.getFase();

    srand(static_cast<unsigned int>(time(0))); // Semente para números aleatórios

    if (escolha == 0 || escolha == 1) {
     
        if (escolha == 0) {

            Fase* faseAtual = nullptr;
            std::ifstream in("save.json");
            json estado;
            in >> estado;

            int fase = estado.value("fase", 1); // valor padrão 1, caso não exista
            
            Jogo jogo(nJog, fase);

            jogo.getFase()->carregarJogo("save.json");

            jogo.executar();
        }

        

        else if (escolha == 1) {
            Jogo jogo(nJog, fase);
            if (fase == 1)
                jogo.getFase()->criarMapa("mapa1.json");
            else if (fase == 2)
                jogo.getFase()->criarMapa("mapa2.json");

            jogo.executar();
        }

        
    }
    else if (escolha == 2) {
        // Leaderboard
    }

    return 0;
}
