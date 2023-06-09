#pragma once
#include "Player.h"
#include<memory>
#include<vector>
#include<unordered_map>
#include<map>

class Game_map
{
private:
	std::map<unsigned int, std::map<unsigned int, Game_square>> squares_first;
	std::map<unsigned int, std::map<unsigned int, Game_square>> squares_second;
	std::vector<std::unique_ptr<Ianimal>> animals;
	std::vector<std::unique_ptr<NPC>> npcs;
	unsigned int gridlength;
	unsigned int gridheight;
	//sf::Vector2f player_position;
	std::vector<sf::Vector2i> npc_positions;
	void set_up_initial_state();
	void set_up_npc_positions();
	void set_up_squares();
	std::string music_path;
	bool play_music;
	sf::Vector2u window_size;
	//sf::RenderWindow& window;
public:
	std::vector<sf::Vector2i>& get_npc_positions();
	unsigned int get_gridlength() const;
	unsigned int get_gridheight() const;
	std::map<unsigned int, std::map<unsigned int, Game_square>>& get_squares_first();
	std::map<unsigned int, std::map<unsigned int, Game_square>>& get_squares_second();
	void update_game_map(sf::RenderTarget&);
	Game_map();
	std::vector<std::unique_ptr<Ianimal>>& get_animals();
	std::vector<std::unique_ptr<NPC>>& get_npcs();
	void set_music_path(std::string);
	std::string get_music_path() const;
	void set_play_music(bool);
	bool get_play_music() const;
	//void set_window_size(sf::RenderWindow&);
	sf::Vector2u get_window_size() const;
	bool check_collision(const Player&);
	//void update_player_pos(sf::Vector2f);
};
