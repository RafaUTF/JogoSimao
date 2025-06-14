#include "Jogo.h"
#include <stdlib.h>

int main()
{
    time_t tempo;
    srand((unsigned)time(&tempo));

    sf::RenderWindow window(sf::VideoMode(1800, 900), "Jogo");

    Menu menu;
    int nJogadores, fase;
    int opcao = menu.mostrar(window, nJogadores, fase);

    if (opcao == 0) {
        Jogo jogo(nJogadores, fase);
    }
    else if (opcao == 1) {
        // tem que fazer
        std::cout << "Leaderboard ainda não implementado.\n";
    }

    return 0;
}
