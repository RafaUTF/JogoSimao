#include "Menu.h"
#include <iostream>

Menu::Menu() : opcaoSelecionada(0) {

    if (!fonte.loadFromFile("arial.ttf")) {
        std::cerr << "Erro ao carregar fonte!\n";
    }

    // Título
    titulo.setFont(fonte);
    titulo.setString("Menu Principal");
    titulo.setCharacterSize(60);
    titulo.setFillColor(sf::Color::White);

    sf::FloatRect boundsTitulo = titulo.getLocalBounds();
    titulo.setOrigin(boundsTitulo.width / 2.0f, boundsTitulo.height / 2.0f);
    titulo.setPosition(1800 / 2.0f, 100);

    // Opções centralizadas
    std::string nomesOpcoes[3] = { "Jogar", "Leaderboard", "Sair" };
    for (int i = 0; i < 3; ++i) {
        opcoes[i].setFont(fonte);
        opcoes[i].setString(nomesOpcoes[i]);
        opcoes[i].setCharacterSize(40);
        opcoes[i].setFillColor(i == 0 ? sf::Color::Blue : sf::Color::White);

        sf::FloatRect bounds = opcoes[i].getLocalBounds();
        opcoes[i].setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
        opcoes[i].setPosition(1800 / 2.0f, 250 + i * 80);
    }

    for (int i = 0; i < 2; ++i) {
        seletores[i].setFont(fonte);
        seletores[i].setCharacterSize(30);
        seletores[i].setFillColor(sf::Color::White);
    }

    seletores[0].setPosition(1800 / 2.0f, 490); // Jogadores
    seletores[1].setPosition(1800 / 2.0f, 540); // Fase

    // Fundo
    if (!texturaFundo.loadFromFile("fundomenu.png")) {
        std::cerr << "Erro ao carregar fundo_menu.png\n";
    }
    else {
        spriteFundo.setTexture(texturaFundo);
        spriteFundo.setScale(
            1800.0f / texturaFundo.getSize().x,
            900.0f / texturaFundo.getSize().y
        );
    }
}

int Menu::mostrar(sf::RenderWindow& window, int& nJogadores, int& fase) {
    nJogadores = 1;
    fase = 1;

    // Inicializa seletores
    seletores[0].setString(std::to_string(nJogadores) + " Jogador(es)");
    seletores[1].setString("Fase " + std::to_string(fase));

    // Centraliza
    for (int i = 0; i < 2; ++i) {
        sf::FloatRect b = seletores[i].getLocalBounds();
        seletores[i].setOrigin(b.width / 2.0f, b.height / 2.0f);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::Up:
                    if (opcaoSelecionada > 0) opcaoSelecionada--;
                    break;
                case sf::Keyboard::Down:
                    if (opcaoSelecionada < 2) opcaoSelecionada++;
                    break;
                case sf::Keyboard::Left:
                    if (opcaoSelecionada == 0 && nJogadores > 1) nJogadores--;
                    break;
                case sf::Keyboard::Right:
                    if (opcaoSelecionada == 0 && nJogadores < 2) nJogadores++;
                    break;
                case sf::Keyboard::A:
                    if (opcaoSelecionada == 0 && fase > 1) fase--;
                    break;
                case sf::Keyboard::D:
                    if (opcaoSelecionada == 0 && fase < 2) fase++;
                    break;
                case sf::Keyboard::Enter:
                    return opcaoSelecionada;
                default:
                    break;
                }

                // Muda cores
                for (int i = 0; i < 3; ++i)
                    opcoes[i].setFillColor(i == opcaoSelecionada ? sf::Color::Blue : sf::Color::White);

                seletores[0].setString(std::to_string(nJogadores) + " Jogador(es)");
                seletores[1].setString("Fase " + std::to_string(fase));

                for (int i = 0; i < 2; ++i) {
                    sf::FloatRect b = seletores[i].getLocalBounds();
                    seletores[i].setOrigin(b.width / 2.0f, b.height / 2.0f);
                }
            }
        }

        window.clear();
        window.draw(spriteFundo);
        window.draw(titulo);
        for (int i = 0; i < 3; ++i)
            window.draw(opcoes[i]);
        if (opcaoSelecionada == 0) {
            for (int i = 0; i < 2; ++i)
                window.draw(seletores[i]);
        }
        window.display();
    }

    return 2;
}
