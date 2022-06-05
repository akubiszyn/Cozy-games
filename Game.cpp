#include "Game.h"

Game::Game(sf::RenderWindow& wind, unsigned int frame_limit) : window(wind), event(sf::Event()), is_end(false), map(Game_map()), player(Player()), is_music_playing(false)
{
	this->window.setFramerateLimit(frame_limit);
}

void Game::update_game()
{
	while (this->window.isOpen())
	{
		if (this->map.get_play_music() == true && this->is_music_playing == false)
		{
			this->music.openFromFile(this->map.get_music_path());
			this->music.setLoop(true);
			this->music.play();
			this->is_music_playing = true;
		}
		else if(this->map.get_play_music() == false)
		{
			this->music.setLoop(false);
			this->music.stop();
			this->is_music_playing = false;
		}
		while (window.pollEvent(this->event))
		{
			if (this->event.type == sf::Event::Closed)
			{
				this->is_end = true;
				this->window.close();
			}
		}
		this->window.clear();
		this->map.update_game_map(this->window);
		this->player.updateMovement(this->map);
		this->player.render(this->window);
		this->window.display();
	}
}


bool Game::get_is_end() const
{
	return this->is_end;
}