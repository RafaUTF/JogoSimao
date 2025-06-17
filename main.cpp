
#include "Jogo.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 900), "Jogo");

    Menu menu;
    int escolha = menu.mostrar(window);
    int nJog = menu.getNJogadores();
    int fase = menu.getFase();

	srand(static_cast<unsigned int>(time(0))); // Semente para números aleatórios

    if (escolha == 0 || escolha == 1) {
        Jogo jogo(nJog, fase);
        if (escolha == 1) jogo.getFase1()->carregarJogo("save.json");
		else if (escolha == 0) jogo.getFase1()->criarMapa("fase1.json");
        jogo.executar();

    }
    else if (escolha == 2) {
        // Leaderboard
    }
    return 0;
}
