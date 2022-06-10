#pragma once
#include "Minigame.h"
class Game
{
private:
	sf::RenderWindow& window;
	sf::Event event;
	bool is_end;
	Game_map map;
	Player player;
	bool is_music_playing;
	bool is_background_music_playing;
	sf::Music music;
	std::vector<std::unique_ptr<Minigame>> minigames;
	//void choose_minigame();
public:
	Game(sf::RenderWindow&, unsigned int);
	void update_game();
	bool get_is_end() const;
	sf::RenderWindow& get_window_ref();
	sf::Event get_event() const;
	Game_map& get_map();
	Player get_player() const;
	bool get_is_music_playing() const;
	bool get_is_background_music_playing() const;
	sf::Music& get_music_ref();
	std::vector<std::unique_ptr<Minigame>>& get_minigames_ref();
};
