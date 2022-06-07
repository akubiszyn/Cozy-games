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
	bool is_minigame_chosen;
	unsigned int minigame_choice;
	sf::Music music;
	std::unique_ptr<Minigame> minigame;
	//void choose_minigame();
public:
	Game(sf::RenderWindow&, unsigned int);
	void update_game();
	bool get_is_end() const;
};