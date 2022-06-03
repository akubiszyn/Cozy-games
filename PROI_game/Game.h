#pragma once
#include "Game_map.h"
class Game
{
private:
	sf::RenderWindow& window;
	sf::Event event;
	bool is_end;
	Game_map map;
public:
	Game(sf::RenderWindow&, unsigned int);
	void update_game();
	bool get_is_end() const;
};