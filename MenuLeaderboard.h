#pragma once
#include "MenuBase.h"
class MenuLeaderboard : public MenuBase
{
	

	public:

	MenuLeaderboard();
	~MenuLeaderboard();
	int mostrar(sf::RenderWindow& window) override;

};

