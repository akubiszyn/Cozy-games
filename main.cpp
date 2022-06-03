#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "PROI GAME");
	Game game(window, 30);
	while (game.get_is_end() == false)
	{
		game.update_game();
	}
}