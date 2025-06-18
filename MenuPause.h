#pragma once
#include "MenuBase.h"

class MenuPause : public MenuBase {
public:
    MenuPause();
    int mostrar(sf::RenderWindow& window) override;
};