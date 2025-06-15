
#include "Jogo.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 900), "Jogo");
    srand(static_cast<unsigned int>(time(0)));
    Menu menu;
    int nJogadores, fase;
    int opcao = menu.mostrar(window, nJogadores, fase);

    if (opcao == 0) {
        Jogo jogo(nJogadores, fase);
    }
    else if (opcao == 1) {
        // tem que fazer
        std::cout << "Leaderboard ainda n�o implementado.\n";
    }

    return 0;
}
