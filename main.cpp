#include "Game.h"
#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "PROI GAME", sf::Style::Fullscreen);
	Game game(window, 30);
	while (game.get_is_end() == false)
	{
		game.update_game();
	}
}
