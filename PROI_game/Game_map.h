#pragma once
#include<SFML/Graphics.hpp>
#include "Game_square.h"
#include<vector>
#include<memory>

class Game_map
{
private:
	std::vector<std::vector<std::unique_ptr<Game_square>>> squares;
	unsigned int gridlength;
	unsigned int gridheight;
	sf::Vector2i player_position;
	std::vector<sf::Vector2i> npc_positions;
	void set_up_initial_state();
	void set_up_npc_positions();
	void set_up_squares();
public:
	std::vector<sf::Vector2i>& get_npc_positions();
	sf::Vector2i get_player_position() const;
	unsigned int get_gridlength() const;
	unsigned int get_gridheight() const;
	std::vector<std::vector<std::unique_ptr<Game_square>>>& get_squares();
	Game_map();
};