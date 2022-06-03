#include "Game_map.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "PROI GAME");
	window.setFramerateLimit(30);
	Game_map map;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		map.update_game_map(window);
		window.display();
	}
}