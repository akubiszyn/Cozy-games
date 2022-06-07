#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "PROI GAME", sf::Style::Fullscreen);
	Game game(window, 30);
	while (game.get_is_end() == false)
	{
		game.update_game();
	}
}
