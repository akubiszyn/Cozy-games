#include "Game.h"

Game::Game(sf::RenderWindow& wind, unsigned int frame_limit) : window(wind), event(sf::Event()), is_end(false), map(Game_map())
{
	this->window.setFramerateLimit(frame_limit);
}

void Game::update_game()
{
	while (this->window.isOpen())
	{
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
		this->window.display();
	}
}

bool Game::get_is_end() const
{
	return this->is_end;
}