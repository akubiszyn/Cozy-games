#pragma once
#include "Player.h"
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
public:
	Game(sf::RenderWindow&, unsigned int);
	void update_game();
	bool get_is_end() const;
};