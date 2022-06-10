#include "Game.h"
#include "Snakeminigame.h"

Game::Game(sf::RenderWindow& wind, unsigned int frame_limit) : window(wind), event(sf::Event()), is_end(false), map(), player(Player(wind.getSize(), sf::Vector2i(14, 8), sf::Vector2i(72, 50), 16, 32, 0.8)), is_music_playing(false), is_background_music_playing(false)
{
	if (frame_limit == 0)
	{
		throw ZeroOccuredException();
	}
	this->window.setFramerateLimit(frame_limit);
}

void Game::update_game()
{
	window.create(sf::VideoMode::getFullscreenModes()[0], "PROI GAME", sf::Style::Fullscreen);
	this->window.setFramerateLimit(30);
	this->minigames.push_back(std::make_unique<Clicking_minigame>(Clicking_minigame()));
	this->minigames.push_back(std::make_unique<JumpingMinigame>(JumpingMinigame()));
	this->minigames.push_back(std::make_unique<DestroyBlockMinigame>(DestroyBlockMinigame()));
	this->minigames.push_back(std::make_unique<Snakegame>(Snakegame()));
	while (this->window.isOpen())
	{
		for (auto& npc_ptr : this->map.get_npcs()) {
			if (npc_ptr->startGame)
			{
				npc_ptr->startGame = false;
				auto it = std::find(map.get_npcs().begin(), map.get_npcs().end(), npc_ptr);
				int index = it - map.get_npcs().begin();
				this->music.stop();
				this->minigames[index]->start(this->window);
				this->music.setLoop(true);
				this->music.play();

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
						if (this->event.key.code == sf::Keyboard::Tab)
						{
							this->is_end = true;
							this->window.close();
						}
					}
				}
				this->window.clear();
				this->map.update_game_map(this->window);
				sf::Vector2f vec = this->player.updateMovement();
				if (this->map.check_collision(this->player))
				{
					if(vec.x != 0)
						this->player.get_sprite_ref().move(-this->player.get_movement_x(), 0.f);
					else
						this->player.get_sprite_ref().move(0.f , -this->player.get_movement_y());
				}
				this->player.render(this->window);
				this->window.display();
			}
		}

	}
}

bool Game::get_is_end() const
{
	return this->is_end;
}

sf::RenderWindow& Game::get_window_ref()
{
	return this->window;
}

sf::Event Game::get_event() const
{
	return this->event;
}

Game_map& Game::get_map()
{
	return this->map;
}

Player Game::get_player() const
{
	return this->player;
}

bool Game::get_is_music_playing() const
{
	return this->is_music_playing;
}

bool Game::get_is_background_music_playing() const
{
	return this->is_background_music_playing;
}

sf::Music& Game::get_music_ref()
{
	return this->music;
}

std::vector<std::unique_ptr<Minigame>>& Game::get_minigames_ref()
{
	return this->minigames;
}
