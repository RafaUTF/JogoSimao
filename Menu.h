#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Menu {
private:
    sf::Font fonte;
    sf::Text titulo;
    sf::Text opcoes[3];       // Jogar, Leaderboard, Sair
    sf::Text seletores[2];    // Jogadores e Fase
    int opcaoSelecionada;

    sf::Texture texturaFundo;
    sf::Sprite spriteFundo;

public:
    Menu();
    ~Menu();
    int mostrar(sf::RenderWindow& window, int& nJogadores, int& fase);
};

