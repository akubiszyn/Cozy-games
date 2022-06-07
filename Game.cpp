#include "Game.h"

Game::Game(sf::RenderWindow& wind, unsigned int frame_limit) : window(wind), event(sf::Event()), is_end(false), map(Game_map(wind)), player(Player(wind)), is_music_playing(false), is_background_music_playing(false), is_minigame_chosen(false), minigame_choice(0)
{
	this->window.setFramerateLimit(frame_limit);
}

void Game::update_game()
{
	while (this->window.isOpen())
	{
		if (this->is_minigame_chosen)
		{
			//this->choose_minigame(this->minigame_choice);
			this->minigame = std::make_unique<Clicking_minigame>(Clicking_minigame());
			this->minigame->start(this->window);
			this->is_minigame_chosen = false;
			this->window.create(sf::VideoMode::getFullscreenModes()[0], "PROI GAME", sf::Style::Fullscreen);

			this->window.setFramerateLimit(30);
		}
		else
		{
			if (this->map.get_play_music() == true && this->is_music_playing == false)
			{
				this->is_background_music_playing = false;
				this->music.openFromFile(this->map.get_music_path());
				this->music.setLoop(true);
				this->music.play();
				this->is_music_playing = true;
			}
			else if (this->map.get_play_music() == false)
			{
				if (!this->is_background_music_playing)
				{
					this->music.stop();
					this->is_music_playing = false;
					this->music.openFromFile("music/background.ogg");
					this->music.setLoop(true);
					this->music.play();
					this->is_background_music_playing = true;
				}


			}
			while (window.pollEvent(this->event))
			{
				if (this->event.type == sf::Event::Closed)
				{
					this->is_end = true;
					this->window.close();
				}
				if (this->event.type == sf::Event::KeyPressed)
				{
					if (this->event.key.code == sf::Keyboard::Escape)
					{
						this->is_end = true;
						this->window.close();
					}
				}
			}
			this->window.clear();
			this->map.update_game_map(this->window);
			this->player.updateMovement(this->map);
			this->player.render(this->window);
			this->window.display();
			this->minigame_choice = this->map.get_minigame_choice();
			if (this->minigame_choice != 0)
			{
				this->is_minigame_chosen = true;
			}
			else
			{
				this->is_minigame_chosen = false;
			}
		}
	}
}


bool Game::get_is_end() const
{
	return this->is_end;
}