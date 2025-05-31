
#include "Jogo.h"

int main()
{
    Jogo jogo;
    return 0;
}
/*
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Criar a janela
    sf::RenderWindow window(sf::VideoMode(800, 600), "Exemplo de Sprite com SFML 2.6.2");
    window.setFramerateLimit(60);

    // Carregar a textura
    sf::Texture texture;
    if (!texture.loadFromFile("mario.png")) {
        std::cerr << "Erro ao carregar a textura!" << std::endl;
        return 1;
    }

    // Criar o sprite e configurar
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Redimensionar o sprite (escala de 50%)
    sprite.setScale(0.5f, 0.5f);

    // Posição inicial
    sprite.setPosition(100.0f, 100.0f);

    // Velocidade de movimento
    sf::Vector2f velocity(2.0f, 1.5f);

    // Loop principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Mover o sprite
        sprite.move(velocity);

        // Verifica bordas e rebate
        sf::Vector2f pos = sprite.getPosition();
        if (pos.x < 0 || pos.x + sprite.getGlobalBounds().width > window.getSize().x)
            velocity.x = -velocity.x;
        if (pos.y < 0 || pos.y + sprite.getGlobalBounds().height > window.getSize().y)
            velocity.y = -velocity.y;

        // Desenhar
        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}

*/