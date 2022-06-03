#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include <iostream>
#include <string>
#include "Player.h"

using namespace sf;

int main() {

	RenderWindow window(VideoMode(640, 480), "SFML Tutorial", Style::Default);
	window.setFramerateLimit(60);


	//Player init
	Player player;
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		//Update player
		player.updateMovement();


		//Draw
		window.clear(Color(150, 150, 150));

		//Draw everything
		player.render(window);


		window.display();
	}
}
