
#include "Jogo.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1800, 900), "Jogo");

    Menu menu;
    int escolha = menu.mostrar(window);
    int nJog = menu.getNJogadores();
    int fase = menu.getFase();

	srand(static_cast<unsigned int>(time(0))); // Semente para números aleatórios

    
        Jogo jogo(nJog, fase);
        if (escolha == 0) 
            jogo.getFase()->carregarJogo("save.json"); // agora 0 é Carregar
        else if (escolha == 1) {
            if(fase == 1)
                jogo.getFase()->criarMapa("mapa1.json"); 
			else if (fase == 2)
				jogo.getFase()->criarMapa("mapa2.json");
        }
        jogo.executar();
    if (escolha == 2) {
        // Leaderboard
    }
    return 0;
}
