#include<SFML/Graphics.hpp>
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
		for (const std::vector<std::unique_ptr<Game_square>>& vec : map.get_squares())
		{
			for (const std::unique_ptr<Game_square>& ptr : vec)
			{
				window.draw(ptr->get_sprite());
			}
		}
		window.display();
	}
}