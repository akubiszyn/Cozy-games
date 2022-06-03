#pragma once
#include "Game_square.h"
#include<vector>
#include<memory>
#include<map>

class Game_map
{
private:
	std::map<unsigned int, std::map<unsigned int, std::unique_ptr<Game_square>>> squares;
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
	std::map<unsigned int, std::map<unsigned int, std::unique_ptr<Game_square>>>& get_squares();
	void update_game_map(sf::RenderTarget&);
	Game_map();
};