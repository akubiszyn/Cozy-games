#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 992), "PROI GAME");
	Game game(window, 30);
	while (game.get_is_end() == false)
	{
		game.update_game();
	}
}
